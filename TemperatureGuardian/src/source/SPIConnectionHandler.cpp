/*
 * SPIConnectionHandler.cpp
 *
 *  Created on: 27 Apr 2017
 *      Author: tobias
 */
#include "../header/SPIConnectionHandler.hpp"

SPIConnectionHandler::SPIConnectionHandler()
: m_Mode(0)
, m_BitsPerWord(0)
, m_Speed(0)
, m_cs0Fd(0)
, m_cs1Fd(0) {

}

SPIConnectionHandler::~SPIConnectionHandler() {

}

int SPIConnectionHandler::openPort (int spiDevice) {
	int status_value = -1;
	int *spi_cs_fd;

	//----- SET SPI MODE -----
	//SPI_MODE_0 (0,0) 	CPOL = 0, CPHA = 0, Clock idle low, data is clocked in on rising edge, output data (change) on falling edge
	//SPI_MODE_1 (0,1) 	CPOL = 0, CPHA = 1, Clock idle low, data is clocked in on falling edge, output data (change) on rising edge
	//SPI_MODE_2 (1,0) 	CPOL = 1, CPHA = 0, Clock idle high, data is clocked in on falling edge, output data (change) on rising edge
	//SPI_MODE_3 (1,1) 	CPOL = 1, CPHA = 1, Clock idle high, data is clocked in on rising, edge output data (change) on falling edge
	m_Mode = SPI_MODE_0;

	//----- SET BITS PER WORD -----
	m_BitsPerWord = 8;

	//----- SET SPI BUS SPEED -----
	m_Speed = 1000000;		//1000000 = 1MHz (1uS per bit)


	if (spiDevice == 1) {
		spi_cs_fd = &m_cs1Fd;
	}
	else {
		spi_cs_fd = &m_cs0Fd;
	}


	if (spiDevice) {
		*spi_cs_fd = open(std::string("/dev/spidev0.1").c_str(), O_RDWR);
	}
	else {
		*spi_cs_fd = open(std::string("/dev/spidev0.0").c_str(), O_RDWR);
	}

	if (*spi_cs_fd < 0) {
		perror("Error - Could not open SPI device");
		exit(1);
	}

	status_value = ioctl(*spi_cs_fd, SPI_IOC_WR_MODE, &m_Mode);
	if(status_value < 0) {
		perror("Could not set SPIMode (WR)...ioctl fail");
		exit(1);
	}

	status_value = ioctl(*spi_cs_fd, SPI_IOC_RD_MODE, &m_Mode);
	if(status_value < 0) {
		perror("Could not set SPIMode (RD)...ioctl fail");
		exit(1);
	}

	status_value = ioctl(*spi_cs_fd, SPI_IOC_WR_BITS_PER_WORD, &m_BitsPerWord);
	if(status_value < 0) {
		perror("Could not set SPI bitsPerWord (WR)...ioctl fail");
		exit(1);
	}

	status_value = ioctl(*spi_cs_fd, SPI_IOC_RD_BITS_PER_WORD, &m_BitsPerWord);
	if(status_value < 0) {
		perror("Could not set SPI bitsPerWord(RD)...ioctl fail");
		exit(1);
	}

	status_value = ioctl(*spi_cs_fd, SPI_IOC_WR_MAX_SPEED_HZ, &m_Speed);
	if(status_value < 0) {
		perror("Could not set SPI speed (WR)...ioctl fail");
		exit(1);
	}

	status_value = ioctl(*spi_cs_fd, SPI_IOC_RD_MAX_SPEED_HZ, &m_Speed);
	if(status_value < 0) {
		perror("Could not set SPI speed (RD)...ioctl fail");
		exit(1);
	}
	return(status_value);
}

int SPIConnectionHandler::closePort (int spiDevice) {
	int status_value = -1;
	int* spi_cs_fd;

	if (spiDevice) {
		spi_cs_fd = &m_cs1Fd;
	}
	else {
		spi_cs_fd = &m_cs0Fd;
	}

	status_value = close(*spi_cs_fd);
	if(status_value < 0) {
		perror("Error - Could not close SPI device");
		exit(1);
	}
	return(status_value);
}

int SPIConnectionHandler::getCS0Fd() {
	return m_cs0Fd;
}

int SPIConnectionHandler::getCS1Fd() {
	return m_cs1Fd;
}

int SPIConnectionHandler::getSpeed() {
	return m_Speed;
}

int SPIConnectionHandler::getBitsPerWord() {
	return m_BitsPerWord;
}
