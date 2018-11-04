/*
 * Message.hh
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#ifndef COMMON_MESSAGE_HH_
#define COMMON_MESSAGE_HH_

#include <string>
#include <cstring>
#include "../Utils/MessageHeaders.hh"

class Message
{
	public:
		Message(std::string unique_param);
		Message(MsgHeader header1, MsgHeader header2, int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);
		Message(MsgHeader header1, MsgHeader header2, std::string param1 = "0", std::string param2 = "0", std::string param3 = "0", std::string param4 = "0");
		virtual ~Message() {};

		void getContent(char* content) { std::strcpy(content, messageContent); }

	private:

		char messageContent[256];
};

#endif /* COMMON_MESSAGE_HH_ */
