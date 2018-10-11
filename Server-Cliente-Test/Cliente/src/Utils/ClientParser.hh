/*
 * ClientParser.hh
 *
 *  Created on: Oct 1, 2018
 *      Author: Synergy
 */

#ifndef CLIENT_PARSER_HH_
#define CLIENT_PARSER_HH_

#include <string>
#include "../data/tinyxml/tinyxml.h"
#include "../data/tinyxml/tinystr.h"
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include "../Utils/Constants.hh"
#include "../Utils/Logger.hh"
#include <list>

namespace std {

class ClientParser {
private:
	string ip;
	int port;

	//Others attributes
	bool fileConfigLoaded;
	bool defaultfileConfigLoaded;
	TiXmlDocument* tiXmlFileConfig;
	TiXmlDocument* tiXmlDefaultFileConfig;

public:
	ClientParser();
	virtual ~ClientParser();

	bool evaluateTagConnection();
	bool evaluateDataXML();
	bool loadConfiguration();
	void testDataClientParser();

	const string& getIp() const;
	void setIp(const string& ip);
	int getPort() const;
	void setPort(int port);
};

} /* namespace std */

#endif /* CLIENT_PARSER_HH_ */
