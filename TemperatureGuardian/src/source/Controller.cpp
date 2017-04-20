/*
 * Controller.cpp
 *
 *  Created on: 20 Apr 2017
 *      Author: tobias
 */
#include "../header/Controller.hpp"

	Controller::Controller() {

	}

	Controller::~Controller() {

	}

	void Controller::startController() {

	}

	void Controller::stopController() {

	}

	void Controller::reportSensorUp(uint8_t sensorPos) {

	}

	void Controller::reportSensorDown(uint8_t sensorPos) {

	}

	void Controller::addSensor(uint8_t sensorPos) {
		SensorHandler* sensor =  new SensorHandler(sensorPos);
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
