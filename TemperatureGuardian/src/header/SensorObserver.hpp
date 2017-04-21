/*
 * SensorObserver.hpp
 *
 *  Created on: 21 Apr 2017
 *      Author: tobias
 */
#pragma once

#ifndef HEADER_SENSOROBSERVER_HPP_
#define HEADER_SENSOROBSERVER_HPP_

//SensorObserver Interface
class SensorObserver {
public:

	virtual ~SensorObserver() {};

	virtual void reportTemperature(int temperature, uint8_t sensorID) = 0;

};

#endif /* HEADER_SENSOROBSERVER_HPP_ */
