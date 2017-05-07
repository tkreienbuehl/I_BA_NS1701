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
	, m_running(false)
	, m_SensorObserver(NULL) {
	m_RawDigitalValServer = RawDigitalValueServer::getInstance();
}

SensorHandler::~SensorHandler() {
	m_running = false;
}

void SensorHandler::registerSensorObserver(SensorObserver* observer) {
	m_SensorObserver = observer;
}

void* SensorHandler::startSensorHandler(void* params) {
	SensorHandler* me = static_cast<SensorHandler*>(params);
	me->doWork();
	pthread_exit(NULL);
	return me;
}

void SensorHandler::stopSensorHandler() {
	m_running = false;
}

uint8_t SensorHandler::getSensorID() {
	return m_SensorID;
}

void SensorHandler::doWork() {
	m_running = true;
	while (m_running) {
		if (m_SensorObserver != NULL) {
			m_SensorObserver->reportTemperature(getTemperature(), m_SensorID);
		}
		usleep(2000000);
	}
}

int SensorHandler::calcTempFromValue(int rawSensorValue) {
	return static_cast<int>(static_cast<float>((rawSensorValue * 3.3 / 1024) - 0.5) * 100);
}

int SensorHandler::getTemperature() {
	int rawTempVal = m_RawDigitalValServer->getRawDigitalValue(m_SensorID);
	return calcTempFromValue(rawTempVal);
}



