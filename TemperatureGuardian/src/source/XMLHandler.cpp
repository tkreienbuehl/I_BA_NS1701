/*
 * XMLWriter.cpp
 *
 *  Created on: 27 Apr 2017
 *      Author: tobias
 */
#include "../header/XMLHandler.hpp"

XMLHandler::XMLHandler() {

	pugi::xml_parse_result result = m_xmlDocument.load_file("/var/www/html/sensordata.xml");
	if (!result) {
		std::cout << "Load result: " << result.description() << std::endl;
	}
	else {
		pugi::xml_node node = m_xmlDocument.first_child();
		if (!node.find_child_by_attribute("id", "SensorValues")) {
			pugi::xml_node child = node.append_child("SensorValues");
			child.append_attribute("id") = "SensorValues";
			m_xmlDocument.save_file("sensordata.xml");
		}
	}
}

XMLHandler::~XMLHandler() {
}

void XMLHandler::writeSensorData(uint8_t sensorNr, int value) {
	pugi::xml_node node = m_xmlDocument.first_child();
	node = node.find_child_by_attribute("id", "SensorValues");
	char str[10];
	sprintf(str, "%i", sensorNr);
	if (!node.find_child_by_attribute("id", str)) {
		pugi::xml_node child = node.append_child("Sensor");
		child.append_attribute("id") = sensorNr;
		child.append_attribute("value") = value;
		m_xmlDocument.save_file("/var/www/html/sensordata.xml");
	}
	else {
		pugi::xml_node child = node.find_child_by_attribute("id", str);
		pugi::xml_attribute attr = child.attribute("value");
		attr.set_value(value);
		m_xmlDocument.save_file("sensordata.xml");
	}
}

void XMLHandler::removeSensor(uint8_t sensorNr) {
	pugi::xml_node node = m_xmlDocument.first_child();
	node = node.find_child_by_attribute("id", "SensorValues");
	char str[10];
	sprintf(str, "%i", sensorNr);
	if (node.find_child_by_attribute("id", str)) {
		node.remove_child(node.find_child_by_attribute("id", str));
		m_xmlDocument.save_file("/var/www/html/sensordata.xml");
	}
}

bool XMLHandler::checkSensorPosLocked(uint8_t sensorNr) {
	pugi::xml_node node = m_xmlDocument.first_child();
	node = node.find_child_by_attribute("id", "LockedSensors");
	char str[10];
	sprintf(str, "%i", sensorNr);
	if (node.find_child_by_attribute("id", str)) {
		return true;
	}
	return false;
}

int XMLHandler::getTemperatureLimit() {
	pugi::xml_node node = m_xmlDocument.first_child();
	node = node.find_child_by_attribute("id", "Settings");
	node = node.find_child_by_attribute("id", "TemperatureLimit");
	return node.attribute("value").as_int();
}

bool XMLHandler::getAlertState() {
	pugi::xml_node node = m_xmlDocument.first_child();
	node = node.find_child_by_attribute("id", "Settings");
	node = node.find_child_by_attribute("id", "AlertState");
	return node.attribute("value").as_bool();
}

void XMLHandler::setAlertState() {
	pugi::xml_node node = m_xmlDocument.first_child();
	node = node.find_child_by_attribute("id", "Settings");
	node = node.find_child_by_attribute("id", "AlertState");
	pugi::xml_attribute attr = node.attribute("value");
	attr.set_value(true);
	m_xmlDocument.save_file("/var/www/html/sensordata.xml");
}
