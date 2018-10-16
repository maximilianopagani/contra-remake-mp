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

class MessageServer
{
	public:
		MessageServer(std::string unique_param);
		MessageServer(MsgDestHeader header1, MsgCmdHeader header2, int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);
		MessageServer(MsgDestHeader header1, MsgCmdHeader header2, std::string param1 = "0", std::string param2 = "0", std::string param3 = "0", std::string param4 = "0");
		virtual ~MessageServer() {};

		void getContent(char* content) { std::strcpy(content, messageContent); }
		int getSize() { return messageSize; }

	private:

		char messageContent[256];
		int messageSize;
};

#endif /* COMMON_MESSAGE_HH_ */
