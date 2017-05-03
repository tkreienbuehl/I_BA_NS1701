/*
 * XMLWriter.hpp
 *
 *  Created on: 27 Apr 2017
 *      Author: tobias
 */

#pragma once

#ifndef HEADER_XMLWRITER_HPP_
#define HEADER_XMLWRITER_HPP_

#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include "pugixml.hpp"
#include <cstdio>

class XMLWriter {

public:

	XMLWriter();
	~XMLWriter();

	void writeSensorData(uint8_t sensorNr, int value);

private:

	pugi::xml_document m_xmlDocument;

};

#endif /* HEADER_XMLWRITER_HPP_ */
