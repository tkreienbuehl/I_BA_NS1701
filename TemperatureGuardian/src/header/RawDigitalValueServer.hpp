/*
 * RawDigitalValueServer.hpp
 *
 *  Created on: 20 Apr 2017
 *      Author: tobias
 */
#pragma once

#ifndef HEADER_RAWDIGITALVALUESERVER_HPP_
#define HEADER_RAWDIGITALVALUESERVER_HPP_

#include <unistd.h>
#include <stdint.h>
#include "SPIDataHandler.hpp"
#include <vector>
#include <algorithm>

class RawDigitalValueServer {

private:

	RawDigitalValueServer();										// Constructor
	RawDigitalValueServer(RawDigitalValueServer const&);			// Copy constructor not implemented!
	RawDigitalValueServer& operator=(RawDigitalValueServer const&);	// assignment operator not implemented!

	~RawDigitalValueServer();

public:

	static RawDigitalValueServer* getInstance();
	static void releaseInstance();

	int getRawDigitalValue(uint8_t sensorID);

private:

	static RawDigitalValueServer* m_Instance;
	SPIDataHandler* m_DataHandler;
	pthread_mutex_t m_mutex;

};

#endif /* HEADER_RAWDIGITALVALUESERVER_HPP_ */
