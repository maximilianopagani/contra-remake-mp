/*
 * ServerParser.hh
 *
 *  Created on: Oct 2, 2018
 *      Author: Synergy
 */

#ifndef SERVER_PARSER_HH_
#define SERVER_PARSER_HH_

#include <string>
#include "../data/tinyxml/tinyxml.h"
#include "../data/tinyxml/tinystr.h"
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include "../Utils/Constants.hh"
#include "../Utils/Logger.hh"
#include <list>

#include "UserParser.hh"

namespace std {

class ServerParser {
private:
	int maximumquantityclients;
	int port;
	list<UserParser> users;

	//Others attributes
	bool fileConfigLoaded;
	bool defaultfileConfigLoaded;
	TiXmlDocument* tiXmlFileConfig;
	TiXmlDocument* tiXmlDefaultFileConfig;

public:
	ServerParser();
	virtual ~ServerParser();

	bool evaluateTagServer();
	bool evaluateTagUsers();
	bool evaluateDataXML();
	bool loadConfiguration();
	void testDataServerParser();

	int getMaximumquantityclients() const;
	int getPort() const;
	const list<UserParser>& getUsers() const;
};

} /* namespace std */

#endif /* SERVER_PARSER_HH_ */
