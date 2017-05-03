/*
 * SPIConnectionHandler.hpp
 *
 *  Created on: 27 Apr 2017
 *      Author: tobias
 */

#pragma once

#ifndef HEADER_SPICONNECTIONHANDLER_HPP_
#define HEADER_SPICONNECTIONHANDLER_HPP_

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <unistd.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class SPIConnectionHandler {
public:

	SPIConnectionHandler();
	~SPIConnectionHandler();

	/**
	 * Opens an SPI port
	 * @param spiDevice 0=CS0, 1=CS1
	 */
	int openPort (int spiDevice);

	/**
	 * Closes the port
	 */
	int closePort (int spiDevice);

	int getCS0Fd();

	int getCS1Fd();

	int getSpeed();

	int getBitsPerWord();

private:
	uint8_t m_Mode;
	uint8_t m_BitsPerWord;
	int m_Speed;
	int m_cs0Fd;
	int m_cs1Fd;
};

#endif /* HEADER_SPICONNECTIONHANDLER_HPP_ */
