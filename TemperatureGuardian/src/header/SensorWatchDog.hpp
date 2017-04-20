#pragma once

#ifndef __SENSOR_WATCH_DOG_H_
#define __SENSOR_WATCH_DOG_H_

#include "Controller.hpp"
#include "RawDigitalValueServer.hpp"

class SensorWatchDog {

public:
	SensorWatchDog(Controller::Ptr controller);
	~SensorWatchDog();

	static void* startWatchDog(void* params);

	void stopWatchDog();

private:

	void doWork();
	void readSensorValues();

	Controller::Ptr m_Controller;
	RawDigitalValueServer::Ptr m_RawDigitalValServer;
	bool m_running;
	const uint8_t MAX_NR_OF_IO_PINS;

};

#endif //__SENSOR_WATCH_DOG_H_