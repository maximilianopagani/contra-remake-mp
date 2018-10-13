/*
 * Message.hh
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#ifndef COMMON_MESSAGE_HH_
#define COMMON_MESSAGE_HH_

#include <string>

enum MsgDestHeader {
	ERROR,
	INFO,
	REQUEST,
	LOGIN,
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
	CLEAR
};

class Message
{
	public:

		Message(MsgDestHeader param1, MsgCmdHeader param2, int param3 = 0, int param4 = 0, int param5 = 0, int param6 = 0);
		Message(MsgDestHeader param1, MsgCmdHeader param2, std::string param3 = "", std::string param4 = "", std::string param5 = "", std::string param6 = "");
		virtual ~Message() {};

		std::string getContent() { return messageString; }
		int getSize() { return messageSize; }

	private:

		std::string messageString;
		int messageSize;
};

#endif /* COMMON_MESSAGE_HH_ */
