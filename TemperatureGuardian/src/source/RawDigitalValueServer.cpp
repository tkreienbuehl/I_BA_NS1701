/*
 * RawDigitalValueServer.cpp
 *
 *  Created on: 21 Apr 2017
 *      Author: tobias
 */
#include "../header/RawDigitalValueServer.hpp"

RawDigitalValueServer* RawDigitalValueServer::m_Instance = NULL;

RawDigitalValueServer::RawDigitalValueServer()
	: m_DataHandler(new SPIDataHandler()) {
}

RawDigitalValueServer::~RawDigitalValueServer() {
	delete m_DataHandler;
	m_DataHandler = NULL;
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

    int a2dVal = 0;
    int a2dChannel = 0;
    unsigned char data[3];
    char buf[3];

    for  (uint8_t i = 0; i < 13; i++ ) {
        data[0] = 1;  //  first byte transmitted -> start bit
        data[1] = 0b10000000 | ((a2dChannel & 7) << 4); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
        data[2] = 0; // third byte transmitted....don't care

        m_DataHandler->readData(0, data, sizeof(data));

        a2dVal = 0;
        a2dVal = (data[1] << 8) & 0b1100000000; //merge data[1] & data[2] to get result
        a2dVal |= (data[2] & 0xff);
        usleep(5000);

        sprintf(buf, "%u", i);
        std::cout << "The Result of channel " << buf << " is: " << a2dVal << std::endl;
        a2dChannel = i;
    }
    std::cout << "Ende" << std::endl;
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



