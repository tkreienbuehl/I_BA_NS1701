/*
 * EMailSender.cpp
 *
 *  Created on: 5 May 2017
 *      Author: tobias
 */
#include "../header/EMailSender.hpp"

EMailSender::EMailSender()
	: m_SourceAddress("")
	, m_DestinationAddress("")
	, m_HeaderText("")
	, m_MessageText("") {
}

EMailSender::~EMailSender() {

}

int EMailSender::sendEmail() {
	int retVal = -1;
	if (m_SourceAddress == "") {
		perror("Source address not set.");
	}
	if (m_DestinationAddress == "") {
		perror("Destination address not set.");
	}
	if (m_HeaderText == "") {
		perror("Headertext (Subject) not set.");
	}
	if (m_MessageText == "") {
		perror("Mail text not set");
	}
	FILE *mailpipe = popen("/usr/lib/sendmail -t", "w");
	if (mailpipe != NULL) {
		fprintf(mailpipe, "To: %s\n", m_DestinationAddress.c_str());
		fprintf(mailpipe, "From: %s\n", m_SourceAddress.c_str());
		fprintf(mailpipe, "Subject: %s\n\n", m_HeaderText.c_str());
		fwrite(m_MessageText.c_str(), 1, m_MessageText.length(), mailpipe);
		fwrite(".\n", 1, 2, mailpipe);
		pclose(mailpipe);
		retVal = 0;
	}
	else {
		 perror("Failed to invoke sendmail");
	}
    return retVal;
}

void EMailSender::setSourceAddress(std::string source) {
	m_SourceAddress = source;
}

void EMailSender::setDestinationAddress(std::string destination) {
	m_DestinationAddress = destination;
}

void EMailSender::setHeaderText(std::string header) {
	m_HeaderText = header;
}

void EMailSender::setMessageText(std::string text) {
	m_MessageText = text;
}
