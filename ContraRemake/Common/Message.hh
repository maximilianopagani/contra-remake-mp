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

enum MsgDestHeader {
	ERROR,
	INFO,
	REQUEST,
	LOGIN,
	INPUT,
	VIEW,
	PLAYER,
	LEVEL,
	BULLET,
	PLATFORM,
	ENEMY
};

enum MsgCmdHeader {
	NONE,
	KEYS,
	RENDER,
	LOAD,
	CLEAR,
	SHOW
};

class Message
{
	public:
		Message(std::string unique_param);
		Message(MsgDestHeader param1, MsgCmdHeader param2, int param3 = 0, int param4 = 0, int param5 = 0, int param6 = 0);
		Message(MsgDestHeader param1, MsgCmdHeader param2, std::string param3 = "0", std::string param4 = "0", std::string param5 = "0", std::string param6 = "0");
		virtual ~Message() {};

		void getContent(char* content) { std::strcpy(content, messageContent); }
		int getSize() { return messageSize; }

	private:

		char messageContent[256];
		int messageSize;
};

#endif /* COMMON_MESSAGE_HH_ */
