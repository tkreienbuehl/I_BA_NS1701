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
    int a2dChannel = sensorID;
    unsigned char data[3];
    char buf[3];
    sprintf(buf, "%u", a2dChannel);
    std::vector<int> values;
    uint8_t vectorSize = 11;

    for  (uint8_t i = 0; i < vectorSize; i++ ) {
        data[0] = 1;  //  first byte transmitted -> start bit
        data[1] = 0b10000000 | ((a2dChannel & 7) << 4); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
        data[2] = 0; // third byte transmitted....don't care

        m_DataHandler->readData(0, data, sizeof(data));

        a2dVal = 0;
        a2dVal = (data[1] << 8) & 0b1100000000; //merge data[1] & data[2] to get result
        a2dVal |= (data[2] & 0xff);
        usleep(5000);

        values.push_back(a2dVal);
    }
    std::sort(values.begin(), values.end());
    return values.at(vectorSize >> 1);
}



