/*
 * SensorWatchDog.cpp
 *
 *  Created on: 20 Apr 2017
 *      Author: tobias
 */
#include <unistd.h>
#include <iostream>
#include "../header/SensorWatchDog.hpp"

SensorWatchDog::SensorWatchDog(Controller::Ptr controller)
	: MAX_NR_OF_IO_PINS(8)
	, m_running(false)
	, m_Controller(controller){
}

SensorWatchDog::~SensorWatchDog() {

}

void* SensorWatchDog::startWatchDog(void* params) {
	SensorWatchDog* me = static_cast<SensorWatchDog*>(params);
	me->doWork();
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
		usleep(10000000);
	}
}

void SensorWatchDog::readSensorValues() {
	for (uint8_t i = 0; i< MAX_NR_OF_IO_PINS; i++) {
		if (i%2 == 0) {
			m_Controller->reportSensorUp(i);	//TODO implement correct
		}
	}
}
