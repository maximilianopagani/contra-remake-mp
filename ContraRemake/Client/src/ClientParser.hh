/*
 * ClientParser.hh
 *
 *  Created on: 20 oct. 2018
 *      Author: nacho
 */

#ifndef CLIENT_SRC_CLIENTPARSER_HH_
#define CLIENT_SRC_CLIENTPARSER_HH_

#include <string>
#include "../../Server/src/data/tinyxml/tinyxml.h"
#include "../../Server/src/data/tinyxml/tinystr.h"
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include "../../Server/src/Utils/Logger.hh"
#include <list>

#define ZERO "0"
#define TAG_CONNECTION "connection"
#define TAG_IP "ip"
#define TAG_PORT "port"
//const char * FILE_CONFIGURATION_CLIENT = "../Client/src/data/configurationClient.xml";
//const char * DEFAULT_FILE_CONFIGURATION_CLIENT = "../Client/src/data/configurationClientDefault.xml";

namespace std {

class ClientParser {
private:
	string ip;
	string port;

	//Others attributes
	bool fileConfigLoaded;
	bool defaultfileConfigLoaded;
	TiXmlDocument* tiXmlFileConfig;
	TiXmlDocument* tiXmlDefaultFileConfig;

public:
	ClientParser();
	virtual ~ClientParser();

	bool evaluateTags();
	bool loadConfiguration();

	string getIP() const;
	string getPort() const;
};

} /* namespace std */

#endif /* CLIENT_SRC_CLIENTPARSER_HH_ */
