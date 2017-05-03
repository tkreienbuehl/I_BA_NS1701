/*
 * SPIDataHandler.cpp
 *
 *  Created on: 27 Apr 2017
 *      Author: tobias
 */
#include "../header/SPIDataHandler.hpp"

SPIDataHandler::SPIDataHandler()
	: m_ConnHandler(new SPIConnectionHandler())
	, m_ConnectionState(0) {
	m_ConnectionState = m_ConnHandler->openPort(0);
}

SPIDataHandler::~SPIDataHandler() {
	m_ConnHandler->closePort(0);
	delete m_ConnHandler;
	m_ConnHandler = NULL;
}

int SPIDataHandler::readData(int spi_device, uint8_t *data, int length) {
	struct spi_ioc_transfer spi[length];
	int i = 0;
	int retVal = -1;
	int *spi_cs_fd;
	int cs1fd = m_ConnHandler->getCS1Fd();
	int cs0fd = m_ConnHandler->getCS0Fd();

	if (spi_device)
		spi_cs_fd = &cs1fd;
	else
		spi_cs_fd = &cs0fd;

	//one spi transfer for each byte

	for (i = 0 ; i < length ; i++) {
		memset(&spi[i], 0, sizeof (spi[i]));
		spi[i].tx_buf        = (unsigned long)(data + i); // transmit from "data"
		spi[i].rx_buf        = (unsigned long)(data + i) ; // receive into "data"
		spi[i].len           = sizeof(*(data + i)) ;
		spi[i].delay_usecs   = 0;
		spi[i].speed_hz      = m_ConnHandler->getSpeed() ;
		spi[i].bits_per_word = m_ConnHandler->getBitsPerWord();
		spi[i].cs_change = 0;
	}

	retVal = ioctl(*spi_cs_fd, SPI_IOC_MESSAGE(length), &spi) ;

	if(retVal < 0) {
		perror("Error - Problem transmitting spi data..ioctl");
		exit(1);
	}

	return retVal;
}
