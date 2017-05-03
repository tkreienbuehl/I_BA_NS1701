/*
 * SPIDataHandler.hpp
 *
 *  Created on: 27 Apr 2017
 *      Author: tobias
 */

#pragma once

#ifndef HEADER_SPIDATAHANDLER_HPP_
#define HEADER_SPIDATAHANDLER_HPP_

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <unistd.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "SPIConnectionHandler.hpp"

class SPIDataHandler {
public:
	SPIDataHandler();
	~SPIDataHandler();

	int readData(int spi_device, uint8_t *data, int length);

private:

	SPIConnectionHandler* m_ConnHandler;
	int m_ConnectionState;
};



#endif /* HEADER_SPIDATAHANDLER_HPP_ */
