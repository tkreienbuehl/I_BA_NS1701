#pragma once

#ifndef __SENSOR_WATCH_DOG_H_
#define __SENSOR_WATCH_DOG_H_

#include "Controller.hpp"
#include "RawDigitalValueServer.hpp"
#include <stdint.h>

class SensorWatchDog {

public:
	SensorWatchDog(Controller* controller);
	~SensorWatchDog();

	static void* startWatchDog(void* params);

	void stopWatchDog();

private:

	void doWork();
	void readSensorValues();

	RawDigitalValueServer* m_RawDigitalValServer;
	const uint8_t MAX_NR_OF_IO_PINS;
	bool m_running;
	Controller* m_Controller;

};

#endif //__SENSOR_WATCH_DOG_H_
