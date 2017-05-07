/*
 * EMailSender.hpp
 *
 *  Created on: 5 May 2017
 *      Author: tobias
 */

#ifndef HEADER_EMAILSENDER_HPP_
#define HEADER_EMAILSENDER_HPP_

#include <stdio.h>
#include <string.h>
#include <string>
#include <errno.h>

class EMailSender {
public:

	EMailSender();
	~EMailSender();

	int sendEmail();

	void setSourceAddress(std::string source);

	void setDestinationAddress(std::string destination);

	void setHeaderText(std::string header);

	void setMessageText(std::string text);

private:

	std::string m_SourceAddress;
	std::string m_DestinationAddress;
	std::string m_HeaderText;
	std::string m_MessageText;

};



#endif /* HEADER_EMAILSENDER_HPP_ */
