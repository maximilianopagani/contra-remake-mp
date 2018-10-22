/*
 * ClientParser.cpp
 *
 *  Created on: 20 oct. 2018
 *      Author: nacho
 */

#include "ClientParser.hh"

namespace std {

ClientParser::ClientParser() {
	// TODO Auto-generated constructor stub
	this->ip = "";
	this->port = "";

	this->fileConfigLoaded = false;
	this->defaultfileConfigLoaded = false;
	this->tiXmlFileConfig = NULL;
	this->tiXmlDefaultFileConfig = NULL;

}

string ClientParser::getIP() const {
	return ip;
}

string ClientParser::getPort() const {
	return port;
}

bool ClientParser::evaluateTags() {
	bool success = true;
	string strIP;
	string strPort;
	int _port = 0;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);
	TiXmlNode* tagConnectionNode = tiXmlHandle.FirstChild(TAG_CONNECTION).ToNode();

	if (!(tagConnectionNode)){
		LOGGER_DEBUG("TAG_Connection no existe");
		return false;
	}

    //TAG_IP
	TiXmlNode* tagIPNode = tagConnectionNode->FirstChildElement(TAG_IP);
	if ((tagIPNode)&&(tagConnectionNode->FirstChildElement(TAG_IP)->GetText())) {
		strIP.clear();
		strIP.append(tagConnectionNode->FirstChildElement(TAG_IP)->GetText());
	    if (!strIP.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_IP es cero");
	    	success = false;
	    }
	    this->ip = strIP.c_str();
	} else {
		LOGGER_DEBUG("TAG_IP no existe o tiene valores invalidos");
		success = false;
	}

    //TAG_PORT
	TiXmlNode* tagPortNode = tagConnectionNode->FirstChildElement(TAG_PORT);
	if ((tagPortNode)&&(tagConnectionNode->FirstChildElement(TAG_PORT)->GetText())) {
		strPort.clear();
		strPort.append(tagConnectionNode->FirstChildElement(TAG_PORT)->GetText());
	    if (!strPort.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_PORT es cero");
	    	success = false;
	    }

	    _port = atoi(strPort.c_str());
	    if (_port>0) {
	    	this->port = strPort.c_str();
		}else {
			LOGGER_DEBUG("PUERTO DESCARTADO: " + strPort);
			success = false;
		}
	} else {
		LOGGER_DEBUG("TAG_PORT no existe o tiene valores invalidos");
		success = false;
	}

	return success;
}

bool ClientParser::loadConfiguration() {
	bool success = true;

	this->tiXmlFileConfig = new TiXmlDocument ("Client/src/data/configurationClient.xml");
	if (this->tiXmlFileConfig->LoadFile()) {
		this->fileConfigLoaded = true;
		evaluateTags();
	} else {
		this->tiXmlDefaultFileConfig = new TiXmlDocument ("Client/src/data/configurationClientDefault.xml");
		if (this->tiXmlDefaultFileConfig->LoadFile()) {
			this->tiXmlFileConfig = this->tiXmlDefaultFileConfig;
			this->defaultfileConfigLoaded = true;
			evaluateTags();
		} else {
			LOGGER_ERROR("No hay archivos de configuracion del servidor");
			if (this->tiXmlFileConfig) {
				delete this->tiXmlFileConfig;
				this->fileConfigLoaded = false;
			}
			if (this->tiXmlDefaultFileConfig) {
				delete this->tiXmlDefaultFileConfig;
				this->defaultfileConfigLoaded = false;
			}
			success = false;
		}
	}
	return success;
}

ClientParser::~ClientParser() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
