#pragma once

#ifndef __SENSOR_HANDLER_H_
#define __SENSOR_HANDLER_H_

#include <memory>
#include "RawDigitalValueServer.hpp"
#include "SensorObserver.hpp"

class SensorHandler {
public:

	typedef std::shared_ptr<SensorHandler> Ptr;

	SensorHandler(uint8_t sensorID);
	~SensorHandler();

	void registerSensorObserver(SensorObserver* observer);

	static void* startSensorHandler(void* params);

	void stopSensorHandler();
	uint8_t getSensorID();

private:

	void doWork();

	int calcTempFromValue(int rawSensorValue);

	int getTemperature();

	uint8_t m_SensorID;
	bool m_running;
	RawDigitalValueServer* m_RawDigitalValServer;
	SensorObserver* m_SensorObserver;

};

#endif //__SENSOR_HANDLER_H_
