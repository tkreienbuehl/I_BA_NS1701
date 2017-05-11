/*
 * LogMsgWriter.hpp
 *
 *  Created on: 11 May 2017
 *      Author: tobias
 */

#ifndef HEADER_LOGMSGWRITER_HPP_
#define HEADER_LOGMSGWRITER_HPP_

#include <iostream>
#include <cstdio>
#include <ctime>
#include <iomanip>

class LogMsgWriter {
private:
	LogMsgWriter();
	~LogMsgWriter();
	LogMsgWriter(LogMsgWriter const&);				// Copy constructor not implemented!
	LogMsgWriter& operator=(LogMsgWriter const&);	// assignment operator not implemented!

public:

	static LogMsgWriter* getInstance();
	static void releaseInstance();

	void writeLogMsg(std::string message);

private:

	static LogMsgWriter* m_Instance;
};

#endif /* HEADER_LOGMSGWRITER_HPP_ */
