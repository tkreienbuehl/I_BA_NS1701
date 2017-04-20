#pragma once

#ifndef __SENSOR_HANDLER_H_
#define __SENSOR_HANDLER_H_

#include <memory>
#include "RawDigitalValueServer.hpp"

class SensorHandler {
public:

	typedef std::shared_ptr<SensorHandler> Ptr;

	SensorHandler(uint8_t sensorID);
	~SensorHandler();

	static void* startSensorHandler(void* params);

	void stopSensorHandler();
	int getTemperatureValue();
	uint8_t getSensorID();

private:

	void doWork();

	int calcTempFromValue(int rawSensorValue);

	uint8_t m_SensorID;
	bool m_running;
	RawDigitalValueServer::Ptr m_RawDigitalValServer;

};

#endif //__SENSOR_HANDLER_H_
