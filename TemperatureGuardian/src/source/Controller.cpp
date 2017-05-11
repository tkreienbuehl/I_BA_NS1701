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
#include <ctime>
#include <iomanip>

Controller::Controller()
	: m_running(false)
	, m_xmlHandler(new XMLHandler())
	, m_MailSender(new EMailSender)
	, m_LogMsgWriter(LogMsgWriter::getInstance()) {
	pthread_mutex_init(&m_mutex, NULL);
	m_MailSender->setSourceAddress("Temeraturwaechter@enterpriselab.ch");
	m_MailSender->setDestinationAddress("tkreienbuehl@bluewin.ch");
	m_MailSender->setHeaderText("TemperaturWächter online");
	m_MailSender->setMessageText("Der Temperaturwächter wurde gestartet");
	if (m_MailSender->sendEmail() == 0 ) {
		m_LogMsgWriter->writeLogMsg("Start mail sent");
	}
}

Controller::~Controller() {
	std::map<uint8_t, SensorHandler*>::iterator itr = m_SensorPool.begin();
	while (itr != m_SensorPool.end()) {
		removeSensor(itr->second->getSensorID());
		usleep(1000);
		itr++;
	}
	delete m_xmlHandler;
	m_xmlHandler = NULL;
	usleep(1000 * 1000);
}

void Controller::startController() {
	m_running = true;
	while (m_running) {
		usleep(1000 * 1000 * 10);
	}
}

void Controller::stopController() {
	m_running = false;
}

void Controller::reportTemperature(int temperature, uint8_t sensorID) {
	if (m_running) {
		pthread_mutex_lock(&m_mutex);
		char buf[10];
		sprintf(buf, "%u", sensorID);
		m_xmlHandler->writeSensorData(sensorID, temperature);
		if (temperature > m_xmlHandler->getTemperatureLimit()) {
			reportTemperaturLimitReached(sensorID);
		}
		pthread_mutex_unlock(&m_mutex);
	}
}

void Controller::reportSensorUp(uint8_t sensorPos) {
	if (!m_xmlHandler->checkSensorPosLocked(sensorPos)) {
		std::map<uint8_t, SensorHandler*>::iterator itr = m_SensorPool.find(sensorPos);
		if (itr == m_SensorPool.end()) {
			addSensor(sensorPos);
		}
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
	pthread_t thread;
	m_threadsMap.insert(std::make_pair(sensorPos, thread));
	pthread_create(&m_threadsMap.at(sensorPos), NULL, SensorHandler::startSensorHandler, sensor);
	char buf[120];
	sprintf(buf,"New sensor found and activated. Sensor ID = %u", sensorPos);
	std::string msg = buf;
	m_LogMsgWriter->writeLogMsg(msg);
}

void Controller::removeSensor(uint8_t sensorID) {
	std::map<uint8_t, SensorHandler*>::iterator itr = m_SensorPool.find(sensorID);
	if (itr != m_SensorPool.end()) {
		SensorHandler* sensor = itr->second;
		m_SensorPool.erase(itr);
		sensor->stopSensorHandler();
		m_xmlHandler->removeSensor(sensorID);
		usleep(5000 * 1000);
		delete sensor;
		char buf[120];
		sprintf(buf,"Sensor %u stopped working, removed", sensorID);
		std::string msg = buf;
		m_LogMsgWriter->writeLogMsg(msg);
	}
}

void Controller::reportTemperaturLimitReached(uint8_t sensorID) {
	if (m_xmlHandler->getAlertState()) {
		return;
	}
	m_MailSender->setHeaderText("Temperatur zu hoch");
	char buf[160];
	sprintf(buf, "Der Sensor %u hat eine zu hohe Temperatur registriert!", sensorID);
	m_MailSender->setMessageText(buf);
	m_MailSender->sendEmail();
	m_xmlHandler->setAlertOccured();
	m_LogMsgWriter->writeLogMsg("Alert message sent");
}
