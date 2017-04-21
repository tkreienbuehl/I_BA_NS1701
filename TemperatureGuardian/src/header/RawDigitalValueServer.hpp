/*
 * RawDigitalValueServer.hpp
 *
 *  Created on: 20 Apr 2017
 *      Author: tobias
 */
#pragma once

#ifndef HEADER_RAWDIGITALVALUESERVER_HPP_
#define HEADER_RAWDIGITALVALUESERVER_HPP_

#include <memory>

class RawDigitalValueServer {

private:

	RawDigitalValueServer();										// Constructor
	RawDigitalValueServer(RawDigitalValueServer const&) {};			// Copy constructor
	RawDigitalValueServer& operator=(RawDigitalValueServer const&);	// assignment operator

	~RawDigitalValueServer();

public:

	static RawDigitalValueServer* getInstance();
	static void releaseInstance();

	int getRawDigitalValue(uint8_t sensorID);

private:

	static RawDigitalValueServer* m_Instance;

};

#endif /* HEADER_RAWDIGITALVALUESERVER_HPP_ */
