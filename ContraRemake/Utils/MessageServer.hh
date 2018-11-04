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
#include "MessageHeaders.hh"

class MessageServer
{
	public:

		MessageServer(std::string unique_param);
		MessageServer(MsgHeader header1, MsgHeader header2, int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);
		MessageServer(MsgHeader header1, MsgHeader header2, std::string param1 = "0", std::string param2 = "0", std::string param3 = "0", std::string param4 = "0");
		virtual ~MessageServer() {};

		void getContent(char* content) { std::strcpy(content, messageContent); }

		void setPlayerId(int _player_id) { player_id = _player_id; }
		void setUsername(std::string _username) { username = _username; }

		int getPlayerId() { return player_id; }
		std::string getUsername() { return username; }

	private:

		int player_id = -1;
		std::string username = "ERROR";
		char messageContent[256];
};

#endif /* COMMON_MESSAGE_HH_ */
