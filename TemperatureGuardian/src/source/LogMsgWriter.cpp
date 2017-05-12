/*
 * LogMsgWriter.cpp
 *
 *  Created on: 11 May 2017
 *      Author: tobias
 */
#include "../header/LogMsgWriter.hpp"

LogMsgWriter* LogMsgWriter::m_Instance = NULL;

LogMsgWriter::LogMsgWriter() {

}

LogMsgWriter::~LogMsgWriter() {
}

LogMsgWriter* LogMsgWriter::getInstance() {
	if (m_Instance == NULL) {
		m_Instance = new LogMsgWriter;
	}
	return m_Instance;
}

void LogMsgWriter::releaseInstance() {
	delete m_Instance;
	m_Instance = NULL;
}

void LogMsgWriter::writeLogMsg(std::string message) {
	std::time_t timeNow = std::time(NULL);
	std::string dateTime = ctime(&timeNow);
	std::cout << dateTime << " " << message << std::endl;
}
