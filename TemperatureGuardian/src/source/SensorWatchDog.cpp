/*
 * SensorWatchDog.cpp
 *
 *  Created on: 20 Apr 2017
 *      Author: tobias
 */
#include <unistd.h>
#include <iostream>
#include "../header/SensorWatchDog.hpp"

SensorWatchDog::SensorWatchDog(Controller* controller)
	: MAX_NR_OF_IO_PINS(8)
	, m_running(false)
	, m_Controller(controller) {
	m_RawDigitalValServer = RawDigitalValueServer::getInstance();
}

SensorWatchDog::~SensorWatchDog() {
	RawDigitalValueServer::releaseInstance();
}

void* SensorWatchDog::startWatchDog(void* params) {
	SensorWatchDog* me = static_cast<SensorWatchDog*>(params);
	me->doWork();
	pthread_exit(NULL);
	return me;
}

void SensorWatchDog::stopWatchDog() {
	m_running = false;
}

void SensorWatchDog::doWork() {
	m_running = true;
	while (m_running) {
		std::cout << "watchdog running" << std::endl;
		readSensorValues();
		usleep(20 * 1000 * 1000);	//wait 20s
	}
}

void SensorWatchDog::readSensorValues() {
	for (uint8_t i = 0; i< MAX_NR_OF_IO_PINS; i++) {
		if (m_RawDigitalValServer->getRawDigitalValue(i) > 15) {	//TODO: filter invalid sensor data (if needed)
			m_Controller->reportSensorUp(i);
			usleep(10000);
		}
	}
}
