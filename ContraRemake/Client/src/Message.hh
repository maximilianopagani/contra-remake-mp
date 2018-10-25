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
	LOGIN,
	LOGIN_DATA,
	LOGIN_ALREADY_ON,
	KEYS,
	RENDER,
	LOAD,
	CLEAR,
	SHOW,
	GAMEFULL,
	DISCONNECT,
	RECONNECT,
	WAITINGPLAYERS,
	LOST_CONNECTION,
	SERVER_CLOSED
};

class Message
{
	public:
		Message(std::string unique_param);
		Message(MsgDestHeader header1, MsgCmdHeader header2, int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);
		Message(MsgDestHeader header1, MsgCmdHeader header2, std::string param1 = "0", std::string param2 = "0", std::string param3 = "0", std::string param4 = "0");
		virtual ~Message() {};

		void getContent(char* content) { std::strcpy(content, messageContent); }

	private:

		char messageContent[256];
};

#endif /* COMMON_MESSAGE_HH_ */
