/*
 * XMLWriter.hpp
 *
 *  Created on: 27 Apr 2017
 *      Author: tobias
 */

#pragma once

#ifndef HEADER_XMLHANDLER_HPP_
#define HEADER_XMLHANDLER_HPP_

#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include "pugixml.hpp"
#include <cstdio>

class XMLHandler {

public:

	XMLHandler();
	~XMLHandler();

	void writeSensorData(uint8_t sensorNr, int value);

	void removeSensor(uint8_t sensorNr);

	/**
	 * Method to determine if a sensor position is locked
	 * or not
	 * @param sensorNr sensor position
	 * @return true if locked false else
	 */
	bool checkSensorPosLocked(uint8_t sensorNr);

	/**
	 * Method to get the temperature limit
	 * @Return the defined limit
	 */
	int getTemperatureLimit();

	/**
	 * Method to get the alert state
	 * if a mail is sent, state is true
	 * until the value is set to zero in XML-file
	 * @return true if temperature is to high and mail is sent, false else
	 */
	bool getAlertState();

	/**
	 * Method to set in xml that
	 * the limit has been reached an a email is sent
	 */
	void setAlertOccured();

	std::string getEmailSourceAddress();

	std::string getEMailDestinationAddress();

private:

	pugi::xml_document m_xmlDocument;
	std::string m_FilePath;

};

#endif /* HEADER_XMLHANDLER_HPP_ */
