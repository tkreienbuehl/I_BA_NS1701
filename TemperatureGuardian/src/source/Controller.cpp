/*
 * Controller.cpp
 *
 *  Created on: 20 Apr 2017
 *      Author: tobias
 */
#include "../header/Controller.hpp"
#include <unistd.h>
#include <iostream>
#include <cstdio>

Controller::Controller()
	: m_running(false)
	, m_xmlWriter(new XMLWriter()){
}

Controller::~Controller() {
	std::map<uint8_t, SensorHandler*>::iterator itr = m_SensorPool.begin();
	while (itr != m_SensorPool.end()) {
		removeSensor(itr->second->getSensorID());
		usleep(1000);
		itr++;
	}
	delete m_xmlWriter;
	m_xmlWriter = NULL;
	usleep(1000 * 1000);
}

void Controller::startController() {
	m_running = true;
	while (m_running) {
		usleep(10000000);
	}
}

void Controller::stopController() {
	m_running = false;
}

void Controller::reportTemperature(int temperature, uint8_t sensorID) {
	if (m_running) {
		char buf[10], tempBuf[10];
		sprintf(buf, "%u", sensorID);
		sprintf(tempBuf, "%i", temperature);
		std::cout << "Sensor " << buf << " is on and reportet: " << tempBuf << "°C"  << std::endl;
		m_xmlWriter->writeSensorData(sensorID, temperature);
		//TODO implement controlling for Temperature
	}
}

void Controller::reportSensorUp(uint8_t sensorPos) {
	std::map<uint8_t, SensorHandler*>::iterator itr = m_SensorPool.find(sensorPos);
	if (itr == m_SensorPool.end()) {
		addSensor(sensorPos);
	}
}

void Controller::reportSensorDown(uint8_t sensorPos) {
	std::map<uint8_t, SensorHandler*>::iterator itr = m_SensorPool.find(sensorPos);
	if (itr != m_SensorPool.end()) {
		removeSensor(itr->second->getSensorID());
	}
}

void Controller::addSensor(uint8_t sensorPos) {
	SensorHandler* sensor = new SensorHandler(sensorPos);
	sensor->registerSensorObserver(this);
	m_SensorPool.insert(std::make_pair(sensorPos, sensor));
	pthread_create(&m_SensorThreads[sensorPos], NULL, SensorHandler::startSensorHandler, sensor);
}

void Controller::removeSensor(uint8_t sensorID) {
	std::map<uint8_t, SensorHandler*>::iterator itr = m_SensorPool.find(sensorID);
	if (itr != m_SensorPool.end()) {
		SensorHandler* sensor = itr->second;
		m_SensorPool.erase(itr);
		sensor->stopSensorHandler();
		m_xmlWriter->removeSensor(sensorID);
		usleep(5000);
		delete sensor;
	}
}
