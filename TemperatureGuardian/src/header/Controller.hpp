/*
 * Controller.hpp
 *
 *  Created on: 20 Apr 2017
 *      Author: tobias
 */

#pragma once

#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include <map>
#include <pthread.h>
#include <stdint.h>
#include "SensorHandler.hpp"
#include "SensorObserver.hpp"
#include "EMailSender.hpp"
#include "XMLHandler.hpp"

#define MAX_NR_OF_SENSORS 8

class Controller : public SensorObserver {

public:

	Controller();
	~Controller();

	void startController();
	void stopController();

	void reportTemperature(int temperature, uint8_t sensorID);

	void reportSensorUp(uint8_t sensorPos);
	void reportSensorDown(uint8_t sensorPos);

private:

	void addSensor(uint8_t sensorPos);
	void removeSensor(uint8_t sensorID);

	void reportTemperaturLimitReached(uint8_t sensorID);

	pthread_t m_SensorThreads[MAX_NR_OF_SENSORS];
	std::map<uint8_t, SensorHandler*> m_SensorPool;
	bool m_running;
	XMLHandler* m_xmlHandler;
	EMailSender* m_MailSender;
	pthread_mutex_t m_mutex;
};

#endif /* __CONTROLLER_H_ */
