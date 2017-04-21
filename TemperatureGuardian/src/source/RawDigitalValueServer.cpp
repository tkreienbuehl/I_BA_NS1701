/*
 * RawDigitalValueServer.cpp
 *
 *  Created on: 21 Apr 2017
 *      Author: tobias
 */
#include "../header/RawDigitalValueServer.hpp"

RawDigitalValueServer* RawDigitalValueServer::m_Instance = NULL;

RawDigitalValueServer::RawDigitalValueServer() {

}

RawDigitalValueServer::~RawDigitalValueServer() {

}

RawDigitalValueServer* RawDigitalValueServer::getInstance() {
	if (m_Instance == NULL) {
		m_Instance = new RawDigitalValueServer();
	}
	return m_Instance;
}

void RawDigitalValueServer::releaseInstance() {
	delete m_Instance;
	m_Instance = NULL;
}

int RawDigitalValueServer::getRawDigitalValue(uint8_t sensorID) {
	//TODO: replace mock with real implementation
	if (sensorID == 1) {
		return 0;
	}
	if (sensorID == 2) {
		return 42;
	}
	if (sensorID == 3) {
		return 18;
	}
	if (sensorID == 4) {
		return 38;
	}
	if (sensorID == 5) {
		return 0;
	}
	if (sensorID == 6) {
		return 6;
	}
	if (sensorID == 7) {
		return 2;
	}
	if (sensorID == 8) {
		return 44;
	}
	return 0;
}



