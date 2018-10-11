/*
 * ClientParser.cpp
 *
 *  Created on: Oct 1, 2018
 *      Author: Synergy
 */

#include "ClientParser.hh"

namespace std {

ClientParser::ClientParser() {
	// TODO Auto-generated constructor stub
	this->ip = VALUE_EMPTY;
	this->port = 0;

	this->fileConfigLoaded = false;
	this->defaultfileConfigLoaded = false;
	this->tiXmlFileConfig = NULL;
	this->tiXmlDefaultFileConfig = NULL;
}

const string& ClientParser::getIp() const {
	return ip;
}

void ClientParser::setIp(const string& ip) {
	this->ip = ip;
}

int ClientParser::getPort() const {
	return port;
}

bool ClientParser::evaluateTagConnection() {
	bool sucess = true;
	string strIP;
	string strPort;
	int _port = 0;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);
	TiXmlNode* tagConnectionNode = tiXmlHandle.FirstChild(TAG_CLIENT).FirstChild(TAG_CONNECTION).ToNode();

	if (!(tagConnectionNode)){
		LOGGER_DEBUG("TAG_CONNECTION no existe");
		return false;
	}

    //TAG_IP
	TiXmlNode* tagIPNode = tagConnectionNode->FirstChildElement(TAG_IP);
	if ((tagIPNode)&&(tagConnectionNode->FirstChildElement(TAG_IP)->GetText())) {
		strIP.clear();
		strIP.append(tagConnectionNode->FirstChildElement(TAG_IP)->GetText());
	    if (!strIP.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_IP es cero");
	    	sucess = false;
	    }
    	this->ip = strIP;
	} else {
		LOGGER_DEBUG("TAG_IP no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_PORT
	TiXmlNode* tagPortNode = tagConnectionNode->FirstChildElement(TAG_PORT);
	if ((tagPortNode)&&(tagConnectionNode->FirstChildElement(TAG_PORT)->GetText())) {
		strPort.clear();
		strPort.append(tagConnectionNode->FirstChildElement(TAG_PORT)->GetText());
	    if (!strPort.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_PORT es cero");
	    	sucess = false;
	    }
	    _port = atoi(strPort.c_str());
	    if (_port>0) {
	    	this->port = _port;
		}else {
			LOGGER_DEBUG("PUERTO DESCARTADO: " + strPort);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_PORT no existe o tiene valores invalidos");
		sucess = false;
	}

	return sucess;
}

bool ClientParser::evaluateDataXML() {
	bool sucess = true;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);

	sucess = this->evaluateTagConnection();
	if (sucess) {
		LOGGER_DEBUG("TAG_CONNECTION, evaluacion aprobada");
	}

	return sucess;
}

bool ClientParser::loadConfiguration() {
	bool sucess = true;

	this->tiXmlFileConfig = new TiXmlDocument (Constants::FILE_CONFIGURATION_CLIENT);
	if (this->tiXmlFileConfig->LoadFile()) {
		this->fileConfigLoaded = true;
		evaluateDataXML();
	} else {
		this->tiXmlDefaultFileConfig = new TiXmlDocument (Constants::DEFAULT_FILE_CONFIGURATION_CLIENT);
		if (this->tiXmlDefaultFileConfig->LoadFile()) {
			this->tiXmlFileConfig = this->tiXmlDefaultFileConfig;
			this->defaultfileConfigLoaded = true;
			evaluateDataXML();
		} else {
			LOGGER_ERROR("No hay archivos de configuracion del cliente");
			if (this->tiXmlFileConfig) {
				delete this->tiXmlFileConfig;
				this->fileConfigLoaded = false;
			}
			if (this->tiXmlDefaultFileConfig) {
				delete this->tiXmlDefaultFileConfig;
				this->defaultfileConfigLoaded = false;
			}
			sucess = false;
		}
	}
	return sucess;
}

void ClientParser::testDataClientParser() {
}

void ClientParser::setPort(int port) {
	this->port = port;
}

ClientParser::~ClientParser() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
