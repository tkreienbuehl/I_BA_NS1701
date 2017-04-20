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

public:
	typedef std::shared_ptr<RawDigitalValueServer> Ptr;

private:
	RawDigitalValueServer();
	~RawDigitalValueServer();
public:

	static RawDigitalValueServer::Ptr getInstance();
	static void releaseInstance();

	int getRawDigitalValue(uint8_t sensorID);

private:

	static RawDigitalValueServer::Ptr m_Instance;

};

#endif /* HEADER_RAWDIGITALVALUESERVER_HPP_ */
