/*
 * Controller.hpp
 *
 *  Created on: 20 Apr 2017
 *      Author: tobias
 */

#pragma once

#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include <memory>
#include <map>
#include <pthread.h>
#include "SensorHandler.hpp"

#define MAX_NR_OF_SENSORS 8

class Controller {

public:

	typedef std::shared_ptr<Controller> Ptr;

	Controller();
	~Controller();

	void startController();
	void stopController();

	void reportSensorUp(uint8_t sensorPos);
	void reportSensorDown(uint8_t sensorPos);

private:

	void addSensor(uint8_t sensorPos);
	void removeSensor(uint8_t sensorID);

	pthread_t m_SensorThreads[MAX_NR_OF_SENSORS];
	std::map<uint8_t, SensorHandler*> m_SensorPool;

};

#endif /* __CONTROLLER_H_ */
