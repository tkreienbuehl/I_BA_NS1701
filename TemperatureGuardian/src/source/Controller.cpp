/*
 * Controller.cpp
 *
 *  Created on: 20 Apr 2017
 *      Author: tobias
 */
#include "../header/Controller.hpp"
#include <unistd.h>
#include <iostream>

	Controller::Controller()
		: m_running(false) {
	}

	Controller::~Controller() {

	}

	void Controller::startController() {
		m_running = true;
		//Aktueller auto-off;
		uint16_t count = 0;
		while (m_running) {
			//TODO
			if (count >= 25) {
				m_running = false;
			}
			std::cout << "Controller runs" << std::endl;
			count++;
			usleep(1000000);
		}
	}

	void Controller::stopController() {
		m_running = false;
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
		m_SensorPool.insert(std::make_pair(sensorPos, sensor));
		pthread_create(&m_SensorThreads[sensorPos], NULL, SensorHandler::startSensorHandler, sensor);
	}

	void Controller::removeSensor(uint8_t sensorID) {
		std::map<uint8_t, SensorHandler*>::iterator itr = m_SensorPool.find(sensorID);
		if (itr != m_SensorPool.end()) {
			SensorHandler* sensor = itr->second;
			m_SensorPool.erase(itr);
			sensor->stopSensorHandler();
			delete sensor;
		}
	}
