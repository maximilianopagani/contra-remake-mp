/*
 * ServerParser.cpp
 *      Author: synergy
 */

#include "ServerParser.hh"

namespace std {

ServerParser::ServerParser() {
	this->maximumquantityclients = 0;
	this->port = 0;
	this->fileConfigLoaded = false;
	this->defaultfileConfigLoaded = false;
	this->tiXmlFileConfig = NULL;
	this->tiXmlDefaultFileConfig = NULL;

}

int ServerParser::getMaximumquantityclients() const {
	return maximumquantityclients;
}

int ServerParser::getPort() const {
	return port;
}

bool ServerParser::evaluateTagServer() {
	bool sucess = true;
	string strMaximumQuantityClients;
	int maximumQuantityClients = 0;
	string strPort;
	int _port = 0;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);
	TiXmlNode* tagServerNode = tiXmlHandle.FirstChild(TAG_SERVER).ToNode();

	if (!(tagServerNode)){
		LOGGER_DEBUG("TAG_SERVER no existe");
		return false;
	}

    //TAG_MAXIMUMQUANTITYCLIENTS
	TiXmlNode* tagMaximumQuantityClientsNode = tagServerNode->FirstChildElement(TAG_MAXIMUMQUANTITYCLIENTS);
	if ((tagMaximumQuantityClientsNode)&&(tagServerNode->FirstChildElement(TAG_MAXIMUMQUANTITYCLIENTS)->GetText())) {
		strMaximumQuantityClients.clear();
		strMaximumQuantityClients.append(tagServerNode->FirstChildElement(TAG_MAXIMUMQUANTITYCLIENTS)->GetText());
	    if (!strMaximumQuantityClients.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_MAXIMUMQUANTITYCLIENTS es cero");
	    	sucess = false;
	    }

	    maximumQuantityClients = atoi(strMaximumQuantityClients.c_str());
	    if ((maximumQuantityClients>0)&&(maximumQuantityClients<5)) {
	    	this->maximumquantityclients = maximumQuantityClients;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE CLIENTES RECHAZADA: " + strMaximumQuantityClients);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_MAXIMUMQUANTITYCLIENTS no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_PORT
	TiXmlNode* tagPortNode = tagServerNode->FirstChildElement(TAG_PORT);
	if ((tagPortNode)&&(tagServerNode->FirstChildElement(TAG_PORT)->GetText())) {
		strPort.clear();
		strPort.append(tagServerNode->FirstChildElement(TAG_PORT)->GetText());
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

bool ServerParser::evaluateTagUsers() {
	bool sucess = true;
	TiXmlNode* tagIDNode = NULL;
	TiXmlNode* tagNameNode = NULL;
	TiXmlNode* tagPasswordNode = NULL;
	string strID = ZERO;
	int _id = 0;
	string strName = VALUE_EMPTY;
	string strPassword = VALUE_EMPTY;

	UserParser userParser;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);
	TiXmlElement* tagUserElement = tiXmlHandle.FirstChild(TAG_SERVER).FirstChild(TAG_USERS).FirstChild(TAG_USER).ToElement();

	for (tagUserElement; tagUserElement; tagUserElement = tagUserElement->NextSiblingElement()) {
		sucess = true;
		_id = 0;
		strName = VALUE_EMPTY;
		strPassword = VALUE_EMPTY;

		//TAG_ID
		tagIDNode = tagUserElement->FirstChildElement(TAG_ID);
		if ((tagIDNode)&&(tagUserElement->FirstChildElement(TAG_ID)->GetText())) {
			strID.clear();
			strID.append(tagUserElement->FirstChildElement(TAG_ID)->GetText());
		    if (!strID.compare(ZERO)) {
		    	LOGGER_DEBUG("TAG_ID es cero");
		    	sucess = false;
		    }
		    _id = atoi(strID.c_str());
		    if (_id>0) {
		    	userParser.setId(_id);
			}else {
				LOGGER_DEBUG("ID RECHAZADO: " + strID + ", para este usuario");
				sucess = false;
			}
		} else {
			LOGGER_DEBUG("TAG_ID no existe o tiene valores invalidos");
			sucess = false;
		}

		//TAG_NAME
		tagNameNode = tagUserElement->FirstChildElement(TAG_NAME);
		if ((tagNameNode)&&(tagUserElement->FirstChildElement(TAG_NAME)->GetText())) {
			strName.clear();
			strName.append(tagUserElement->FirstChildElement(TAG_NAME)->GetText());
		    if (!strName.compare(VALUE_EMPTY)) {
		    	LOGGER_DEBUG("TAG_NAME esta vacio");
		    	sucess = false;
		    }
		    userParser.setName(strName);
		} else {
			LOGGER_DEBUG("TAG_NAME no existe o tiene valores invalidos");
			sucess = false;
		}

		//TAG_PASSWORD
		tagPasswordNode = tagUserElement->FirstChildElement(TAG_PASSWORD);
		if ((tagPasswordNode)&&(tagUserElement->FirstChildElement(TAG_PASSWORD)->GetText())) {
			strPassword.clear();
			strPassword.append(tagUserElement->FirstChildElement(TAG_PASSWORD)->GetText());
		    if (!strPassword.compare(VALUE_EMPTY)) {
		    	LOGGER_DEBUG("TAG_PASSWORD esta vacio");
		    	sucess = false;
		    }
		    userParser.setPassword(strPassword);
		} else {
			LOGGER_DEBUG("TAG_PASSWORD no existe o tiene valores invalidos");
			sucess = false;
		}

		if (sucess) {
			this->users.push_back(userParser);
			LOGGER_DEBUG("Se ha cargado exitosamente el usuario cuyo ID es: " + strID);
			LOGGER_DEBUG("Este usuario tiene por nombre: " + strName);
			LOGGER_DEBUG("Este usuario tiene por password: " + strPassword);
		}
	}

	return sucess;
}

bool ServerParser::evaluateDataXML() {
	bool sucess = true;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);

	sucess = this->evaluateTagServer();
	if (sucess) {
		LOGGER_DEBUG("TAG_SERVER, evaluacion aprobada");
	}

	TiXmlNode* tagUserNode = tiXmlHandle.FirstChild(TAG_SERVER).FirstChild(TAG_USERS).FirstChild(TAG_USER).ToNode();
	if (tagUserNode) {
		sucess = this->evaluateTagUsers();
		if (sucess) {
			LOGGER_DEBUG("TAG_USERS del servidor, evaluacion aprobada");
		}
	} else {
		LOGGER_DEBUG("TAG_USERS del servidor no existe");
    	return false;
	}

	return sucess;
}

bool ServerParser::loadConfiguration() {
	bool sucess = true;

	this->tiXmlFileConfig = new TiXmlDocument (Constants::FILE_CONFIGURATION_SERVER);
	if (this->tiXmlFileConfig->LoadFile()) {
		this->fileConfigLoaded = true;
		evaluateDataXML();
	} else {
		this->tiXmlDefaultFileConfig = new TiXmlDocument (Constants::DEFAULT_FILE_CONFIGURATION_SERVER);
		if (this->tiXmlDefaultFileConfig->LoadFile()) {
			this->tiXmlFileConfig = this->tiXmlDefaultFileConfig;
			this->defaultfileConfigLoaded = true;
			evaluateDataXML();
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
			sucess = false;
		}
	}
	return sucess;
}

//void ServerParser::testDataServerParser() {
//
//	int maxClients = this->maximumquantityclients;
//	cout << "La cantidad maxima de clientes es: ";
//	cout << maxClients << endl;
//
//	int puerto = this->port;
//	cout << "El puerto de conexion del servidor es: ";
//	cout << puerto << endl;
//
//	cout << "LISTADO DE TODOS LOS CLIENTES" << endl;
//	std::list<UserParser>::iterator it;
//	std::list<UserParser> lista;
//
//	lista = this->getUsers();
//    for (it=lista.begin(); it != lista.end();it++){
//        int id = (*it).getId();
//        string name = (*it).getName();
//        string password = (*it).getName();
//
//    	cout << "El id del usuario es: ";
//    	cout << id << endl;
//    	cout << "El nombre del usuario es: ";
//    	cout << name << endl;
//    	cout << "El password del usuario es: ";
//    	cout << password << endl;
//    }
//}

const list<UserParser>& ServerParser::getUsers() const {
	return users;
}

ServerParser::~ServerParser() {}

}
