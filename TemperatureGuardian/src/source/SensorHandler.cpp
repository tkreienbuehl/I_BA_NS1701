/*
 * SensorHandler.cpp
 *
 *  Created on: 20 Apr 2017
 *      Author: tobias
 */
#include "../header/SensorHandler.hpp"
#include <unistd.h>
#include <iostream>

SensorHandler::SensorHandler(uint8_t sensorID)
	: m_SensorID(sensorID)
	, m_running(false) {
}

SensorHandler::~SensorHandler() {

}

void* SensorHandler::startSensorHandler(void* params) {
	SensorHandler* me = static_cast<SensorHandler*>(params);
	me->doWork();
	return me;
}

void SensorHandler::stopSensorHandler() {
	m_running = false;
}

void SensorHandler::doWork() {
	m_running = true;
	while (m_running) {
		//TODO
		std::cout << "Sensor " << m_SensorID << " is on" << std::endl;
		usleep(2000000);
	}
}

int SensorHandler::getTemperatureValue() {
	return 0; //TODO
}

uint8_t SensorHandler::getSensorID() {
	return m_SensorID;
}

int SensorHandler::calcTempFromValue(int rawSensorValue) {
	return rawSensorValue;	//TODO
}



