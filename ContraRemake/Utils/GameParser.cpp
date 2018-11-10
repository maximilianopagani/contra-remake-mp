#include "GameParser.hh"

GameParser::GameParser() {
	this->tiXmlFileConfig = NULL;
	this->fileConfigLoaded = false;
	this->tiXmlDefaultFileConfig = NULL;
	this->defaultfileConfigLoaded = false;
	this->level = "";
	this->fondo1Nivel1 = "";
	this->fondo2Nivel1 = "";
	this->fondo3Nivel1 = "";
	this->fondo1Nivel2 = "";
	this->fondo2Nivel2 = "";
	this->fondo3Nivel2 = "";
	this->fondo1Nivel3 = "";
	this->fondo2Nivel3 = "";
	this->fondo3Nivel3 = "";
	this->quantityEnemiesLevel1 = 0;
	this->quantityEnemiesLevel2 = 0;
	this->quantityEnemiesLevel3 = 0;

	this->quantitySoldiersLevel1 = 0;
	this->quantitySnipersLevel1 = 0;
	this->quantityGunnersLevel1 = 0;
	this->quantityScubaSoldiersLevel1 = 0;
	this->quantityWallTurretsLevel1 = 0;
	this->quantityCannonsLevel1 = 0;
	this->quantityFloatersLevel1 = 0;
	this->quantitySporesLevel1 = 0;
	this->quantityCrawlersLevel1 = 0;

	this->quantitySoldiersLevel2 = 0;
	this->quantitySnipersLevel2 = 0;
	this->quantityGunnersLevel2 = 0;
	this->quantityScubaSoldiersLevel2 = 0;
	this->quantityWallTurretsLevel2 = 0;
	this->quantityCannonsLevel2 = 0;
	this->quantityFloatersLevel2 = 0;
	this->quantitySporesLevel2 = 0;
	this->quantityCrawlersLevel2 = 0;

	this->quantitySoldiersLevel3 = 0;
	this->quantitySnipersLevel3 = 0;
	this->quantityGunnersLevel3 = 0;
	this->quantityScubaSoldiersLevel3 = 0;
	this->quantityWallTurretsLevel3 = 0;
	this->quantityCannonsLevel3 = 0;
	this->quantityFloatersLevel3 = 0;
	this->quantitySporesLevel3 = 0;
	this->quantityCrawlersLevel3 = 0;
}

bool GameParser::evaluateTagDebug(){
	bool sucess = true;
	string strLevel;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);

	TiXmlNode* tagDebugNode = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_DEBUG).ToNode();

	if (!(tagDebugNode)){
		LOGGER_ERROR("TAG_DEBUG no existe");
	    return false;
	}

    //TAG_LEVEL
	TiXmlNode* tagLevelNode = tagDebugNode->FirstChildElement(TAG_LEVEL);
	if ((tagLevelNode)&&(tagDebugNode->FirstChildElement(TAG_LEVEL)->GetText())) {
		strLevel.clear();
		strLevel.append(tagDebugNode->FirstChildElement(TAG_LEVEL)->GetText());
	    if (!strLevel.compare(VALUE_EMPTY)) {
			LOGGER_ERROR("TAG_LEVEL esta vacio");
	    	sucess = false;
	    }

        this->level = strLevel;
        if (!((this->level.compare("ERROR"))||(this->level.compare("DEBUG"))||(this->level.compare("INFO")))) {
			LOGGER_ERROR("TAG_LEVEL es desconocido");
			sucess = false;
		}

	} else {
		LOGGER_ERROR("TAG_LEVEL no existe o tiene valores invalidos");
		sucess = false;
	}

	if (sucess) {
		if (!(this->level.compare("ERROR"))){
			if (this->fileConfigLoaded == true) {
				LOGGER_INFO("Se ha cargado el archivo de configuracion");
			} else {
				if (this->defaultfileConfigLoaded == true) {
					LOGGER_ERROR("No se ha cargado el archivo de configuracion");
					LOGGER_INFO("Se ha cargado el archivo default de configuracion")
				}
			}
		}

		if (!(this->level.compare("DEBUG"))){
			if (this->fileConfigLoaded == true) {
				LOGGER_INFO("Se ha cargado el archivo de configuracion");
			} else {
				if (this->defaultfileConfigLoaded == true) {
					LOGGER_ERROR("No se ha cargado el archivo de configuracion");
					LOGGER_INFO("Se ha cargado el archivo default de configuracion")
				}
			}
		}

		if (!(this->level.compare("INFO"))){
			if (this->fileConfigLoaded == true) {
				LOGGER_INFO("Se ha cargado el archivo de configuracion");
			} else {
				if (this->defaultfileConfigLoaded == true) {
					LOGGER_ERROR("No se ha cargado el archivo de configuracion");
					LOGGER_INFO("Se ha cargado el archivo default de configuracion")
				}
			}
		}
	}

	return sucess;
}

bool GameParser::evaluateTagNivel1(){
	bool sucess = true;
	string strFondo1;
	string strFondo2;
	string strFondo3;
	string strQuantitySoldiers;
	int quantitySoldiers = 0;
	string strQuantitySnipers;
	int quantitySnipers = 0;
	string strQuantityGunners;
	int quantityGunners = 0;
	string strQuantityScubaSoldiers;
	int quantityScubaSoldiers = 0;
	string strQuantityWallTurrets;
	int quantityWallTurrets = 0;
	string strQuantityCannons;
	int quantityCannons = 0;
	string strQuantityFloaters;
	int quantityFloaters = 0;
	string strQuantitySpores;
	int quantitySpores = 0;
	string strQuantityCrawlers;
	int quantityCrawlers = 0;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);
	TiXmlNode* tagNivel1Node = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_ESCENARIOS).FirstChild(TAG_NIVEL1).ToNode();

	if (!(tagNivel1Node)){
		LOGGER_DEBUG("TAG_NIVEL1 no existe");
		return false;
	}

    //TAG_FONDO1
	TiXmlNode* tagFondo1Node = tagNivel1Node->FirstChildElement(TAG_FONDO1);
	if ((tagFondo1Node)&&(tagNivel1Node->FirstChildElement(TAG_FONDO1)->GetText())) {
		strFondo1.clear();
		strFondo1.append(tagNivel1Node->FirstChildElement(TAG_FONDO1)->GetText());
	    if (!strFondo1.compare(VALUE_EMPTY)) {
	    	LOGGER_DEBUG("TAG_FONDO1 esta vacio");
	    	sucess = false;
	    }

        this->fondo1Nivel1 = strFondo1;
	} else {
		LOGGER_DEBUG("TAG_FONDO1 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_FONDO2
	TiXmlNode* tagFondo2Node = tagNivel1Node->FirstChildElement(TAG_FONDO2);
	if ((tagFondo2Node)&&(tagNivel1Node->FirstChildElement(TAG_FONDO2)->GetText())) {
		strFondo2.clear();
		strFondo2.append(tagNivel1Node->FirstChildElement(TAG_FONDO2)->GetText());
	    if (!strFondo2.compare(VALUE_EMPTY)) {
	    	LOGGER_DEBUG("TAG_FONDO2 esta vacio");
	    	sucess = false;
	    }

        this->fondo2Nivel1 = strFondo2;
	} else {
		LOGGER_DEBUG("TAG_FONDO2 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_FONDO3
	TiXmlNode* tagFondo3Node = tagNivel1Node->FirstChildElement(TAG_FONDO3);
	if ((tagFondo3Node)&&(tagNivel1Node->FirstChildElement(TAG_FONDO3)->GetText())) {
		strFondo3.clear();
		strFondo3.append(tagNivel1Node->FirstChildElement(TAG_FONDO3)->GetText());
	    if (!strFondo3.compare(VALUE_EMPTY)) {
	    	LOGGER_DEBUG("TAG_FONDO3 esta vacio");
	    	sucess = false;
	    }

        this->fondo3Nivel1 = strFondo3;
	} else {
		LOGGER_DEBUG("TAG_FONDO3 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSOLDIERS
	TiXmlNode* tagQuantitySoldiersNode = tagNivel1Node->FirstChildElement(TAG_QUANTITYSOLDIERS);
	if ((tagQuantitySoldiersNode)&&(tagNivel1Node->FirstChildElement(TAG_QUANTITYSOLDIERS)->GetText())) {
		strQuantitySoldiers.clear();
		strQuantitySoldiers.append(tagNivel1Node->FirstChildElement(TAG_QUANTITYSOLDIERS)->GetText());
	    if (!strQuantitySoldiers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSOLDIERS del nivel 1 es cero");
	    	sucess = false;
	    }

	    quantitySoldiers = atoi(strQuantitySoldiers.c_str());
	    if ((quantitySoldiers>0)&&(quantitySoldiers<1000)) {
	    	this->quantitySoldiersLevel1 = quantitySoldiers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SOLDIERS RECHAZADA del nivel 1: " + strQuantitySoldiers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSOLDIERS del nivel 1 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSNIPERS
	TiXmlNode* tagQuantitySnipersNode = tagNivel1Node->FirstChildElement(TAG_QUANTITYSNIPERS);
	if ((tagQuantitySnipersNode)&&(tagNivel1Node->FirstChildElement(TAG_QUANTITYSNIPERS)->GetText())) {
		strQuantitySnipers.clear();
		strQuantitySnipers.append(tagNivel1Node->FirstChildElement(TAG_QUANTITYSNIPERS)->GetText());
	    if (!strQuantitySnipers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSNIPERS del nivel 1 es cero");
	    	sucess = false;
	    }

	    quantitySnipers = atoi(strQuantitySnipers.c_str());
	    if ((quantitySnipers>0)&&(quantitySnipers<1000)) {
	    	this->quantitySnipersLevel1 = quantitySnipers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SNIPERS RECHAZADA del nivel 1 " + strQuantitySnipers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSOLDIERS del nivel 1 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYGUNNERS
	TiXmlNode* tagQuantityGunnersNode = tagNivel1Node->FirstChildElement(TAG_QUANTITYGUNNERS);
	if ((tagQuantityGunnersNode)&&(tagNivel1Node->FirstChildElement(TAG_QUANTITYGUNNERS)->GetText())) {
		strQuantityGunners.clear();
		strQuantityGunners.append(tagNivel1Node->FirstChildElement(TAG_QUANTITYGUNNERS)->GetText());
	    if (!strQuantityGunners.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYGUNNERS del nivel 1 es cero");
	    	sucess = false;
	    }

	    quantityGunners = atoi(strQuantityGunners.c_str());
	    if ((quantityGunners>0)&&(quantityGunners<1000)) {
	    	this->quantityGunnersLevel1 = quantityGunners;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE GUNNERS RECHAZADA del nivel 1: " + strQuantityGunners);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYGUNNERS del nivel 1 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSCUBASOLDIERS
	TiXmlNode* tagQuantityScubaSoldiersNode = tagNivel1Node->FirstChildElement(TAG_QUANTITYSCUBASOLDIERS);
	if ((tagQuantityScubaSoldiersNode)&&(tagNivel1Node->FirstChildElement(TAG_QUANTITYSCUBASOLDIERS)->GetText())) {
		strQuantityScubaSoldiers.clear();
		strQuantityScubaSoldiers.append(tagNivel1Node->FirstChildElement(TAG_QUANTITYSCUBASOLDIERS)->GetText());
	    if (!strQuantityScubaSoldiers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSCUBASOLDIERS del nivel 1 es cero");
	    	sucess = false;
	    }

	    quantityScubaSoldiers = atoi(strQuantityScubaSoldiers.c_str());
	    if ((quantityScubaSoldiers>0)&&(quantityScubaSoldiers<1000)) {
	    	this->quantityScubaSoldiersLevel1 = quantityScubaSoldiers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SCUBASOLDIERS RECHAZADA del nivel 1: " + strQuantityScubaSoldiers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSCUBASOLDIERS del nivel 1 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYWALLTURRETS
	TiXmlNode* tagQuantityWallTurretsNode = tagNivel1Node->FirstChildElement(TAG_QUANTITYWALLTURRETS);
	if ((tagQuantityWallTurretsNode)&&(tagNivel1Node->FirstChildElement(TAG_QUANTITYWALLTURRETS)->GetText())) {
		strQuantityWallTurrets.clear();
		strQuantityWallTurrets.append(tagNivel1Node->FirstChildElement(TAG_QUANTITYWALLTURRETS)->GetText());
	    if (!strQuantityWallTurrets.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYWALLTURRETS del nivel 1 es cero");
	    	sucess = false;
	    }

	    quantityWallTurrets = atoi(strQuantityWallTurrets.c_str());
	    if ((quantityWallTurrets>0)&&(quantityWallTurrets<1000)) {
	    	this->quantityWallTurretsLevel1 = quantityWallTurrets;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE WALLTURRETS RECHAZADA del nivel 1: " + strQuantityWallTurrets);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYWALLTURRETS del nivel 1 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYCANNONS
	TiXmlNode* tagQuantityCannonsNode = tagNivel1Node->FirstChildElement(TAG_QUANTITYCANNONS);
	if ((tagQuantityCannonsNode)&&(tagNivel1Node->FirstChildElement(TAG_QUANTITYCANNONS)->GetText())) {
		strQuantityCannons.clear();
		strQuantityCannons.append(tagNivel1Node->FirstChildElement(TAG_QUANTITYCANNONS)->GetText());
	    if (!strQuantityCannons.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYCANNONS del nivel 1 es cero");
	    	sucess = false;
	    }

	    quantityCannons = atoi(strQuantityCannons.c_str());
	    if ((quantityCannons>0)&&(quantityCannons<1000)) {
	    	this->quantityCannonsLevel1 = quantityCannons;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE CANNONS RECHAZADA del nivel 1: " + strQuantityCannons);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYCANNONS del nivel 1 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYFLOATERS
	TiXmlNode* tagQuantityFloatersNode = tagNivel1Node->FirstChildElement(TAG_QUANTITYFLOATERS);
	if ((tagQuantityFloatersNode)&&(tagNivel1Node->FirstChildElement(TAG_QUANTITYFLOATERS)->GetText())) {
		strQuantityFloaters.clear();
		strQuantityFloaters.append(tagNivel1Node->FirstChildElement(TAG_QUANTITYFLOATERS)->GetText());
	    if (!strQuantityFloaters.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYFLOATERS del nivel 1 es cero");
	    	sucess = false;
	    }

	    quantityFloaters = atoi(strQuantityFloaters.c_str());
	    if ((quantityFloaters>0)&&(quantityFloaters<1000)) {
	    	this->quantityFloatersLevel1 = quantityFloaters;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE FLOATERS RECHAZADA del nivel 1: " + strQuantityFloaters);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYFLOATERS del nivel 1 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSPORES
	TiXmlNode* tagQuantitySporesNode = tagNivel1Node->FirstChildElement(TAG_QUANTITYSPORES);
	if ((tagQuantitySporesNode)&&(tagNivel1Node->FirstChildElement(TAG_QUANTITYSPORES)->GetText())) {
		strQuantitySpores.clear();
		strQuantitySpores.append(tagNivel1Node->FirstChildElement(TAG_QUANTITYSPORES)->GetText());
	    if (!strQuantitySpores.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSPORES del nivel 1 es cero");
	    	sucess = false;
	    }

	    quantitySpores = atoi(strQuantitySpores.c_str());
	    if ((quantitySpores>0)&&(quantitySpores<1000)) {
	    	this->quantitySporesLevel1 = quantitySpores;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SPORES RECHAZADA del nivel 1: " + strQuantitySpores);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSPORES del nivel 1 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYCRAWLERS
	TiXmlNode* tagQuantityCrawlersNode = tagNivel1Node->FirstChildElement(TAG_QUANTITYCRAWLERS);
	if ((tagQuantityCrawlersNode)&&(tagNivel1Node->FirstChildElement(TAG_QUANTITYCRAWLERS)->GetText())) {
		strQuantityCrawlers.clear();
		strQuantityCrawlers.append(tagNivel1Node->FirstChildElement(TAG_QUANTITYCRAWLERS)->GetText());
	    if (!strQuantityCrawlers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYCRAWLERS del nivel 1 es cero");
	    	sucess = false;
	    }

	    quantityCrawlers = atoi(strQuantityCrawlers.c_str());
	    if ((quantityCrawlers>0)&&(quantityCrawlers<1000)) {
	    	this->quantityCrawlersLevel1 = quantityCrawlers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE CRAWLERS RECHAZADA del nivel 1: " + strQuantityCrawlers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYCRAWLERS del nivel 1 no existe o tiene valores invalidos");
		sucess = false;
	}

	return sucess;
}

bool GameParser::evaluateTagNivel2(){
	bool sucess = true;
	string strFondo1;
	string strFondo2;
	string strFondo3;
	string strQuantitySoldiers;
	int quantitySoldiers = 0;
	string strQuantitySnipers;
	int quantitySnipers = 0;
	string strQuantityGunners;
	int quantityGunners = 0;
	string strQuantityScubaSoldiers;
	int quantityScubaSoldiers = 0;
	string strQuantityWallTurrets;
	int quantityWallTurrets = 0;
	string strQuantityCannons;
	int quantityCannons = 0;
	string strQuantityFloaters;
	int quantityFloaters = 0;
	string strQuantitySpores;
	int quantitySpores = 0;
	string strQuantityCrawlers;
	int quantityCrawlers = 0;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);
	TiXmlNode* tagNivel2Node = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_ESCENARIOS).FirstChild(TAG_NIVEL2).ToNode();

	if (!(tagNivel2Node)){
		LOGGER_DEBUG("TAG_NIVEL2 no existe");
    	return false;
    }

    //TAG_FONDO1
	TiXmlNode* tagFondo1Node = tagNivel2Node->FirstChildElement(TAG_FONDO1);
	if ((tagFondo1Node)&&(tagNivel2Node->FirstChildElement(TAG_FONDO1)->GetText())) {
		strFondo1.clear();
		strFondo1.append(tagNivel2Node->FirstChildElement(TAG_FONDO1)->GetText());
	    if (!strFondo1.compare(VALUE_EMPTY)) {
	    	LOGGER_DEBUG("TAG_FONDO1 esta vacio");
	    	sucess = false;
	    }

        this->fondo1Nivel2 = strFondo1;
	} else {
		LOGGER_DEBUG("TAG_FONDO1 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_FONDO2
	TiXmlNode* tagFondo2Node = tagNivel2Node->FirstChildElement(TAG_FONDO2);
	if ((tagFondo2Node)&&(tagNivel2Node->FirstChildElement(TAG_FONDO2)->GetText())) {
		strFondo2.clear();
		strFondo2.append(tagNivel2Node->FirstChildElement(TAG_FONDO2)->GetText());
	    if (!strFondo2.compare(VALUE_EMPTY)) {
	    	LOGGER_DEBUG("TAG_FONDO2 esta vacio");
	    	sucess = false;
	    }

        this->fondo2Nivel2 = strFondo2;
	} else {
		LOGGER_DEBUG("TAG_FONDO2 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_FONDO3
	TiXmlNode* tagFondo3Node = tagNivel2Node->FirstChildElement(TAG_FONDO3);
	if ((tagFondo3Node)&&(tagNivel2Node->FirstChildElement(TAG_FONDO3)->GetText())) {
		strFondo3.clear();
		strFondo3.append(tagNivel2Node->FirstChildElement(TAG_FONDO3)->GetText());
	    if (!strFondo3.compare(VALUE_EMPTY)) {
	    	LOGGER_DEBUG("TAG_FONDO3 esta vacio");
	    	sucess = false;
	    }

        this->fondo3Nivel2 = strFondo3;
	} else {
		LOGGER_DEBUG("TAG_FONDO3 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSOLDIERS
	TiXmlNode* tagQuantitySoldiersNode = tagNivel2Node->FirstChildElement(TAG_QUANTITYSOLDIERS);
	if ((tagQuantitySoldiersNode)&&(tagNivel2Node->FirstChildElement(TAG_QUANTITYSOLDIERS)->GetText())) {
		strQuantitySoldiers.clear();
		strQuantitySoldiers.append(tagNivel2Node->FirstChildElement(TAG_QUANTITYSOLDIERS)->GetText());
	    if (!strQuantitySoldiers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSOLDIERS del nivel 2 es cero");
	    	sucess = false;
	    }

	    quantitySoldiers = atoi(strQuantitySoldiers.c_str());
	    if ((quantitySoldiers>0)&&(quantitySoldiers<1000)) {
	    	this->quantitySoldiersLevel2 = quantitySoldiers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SOLDIERS RECHAZADA del nivel 2: " + strQuantitySoldiers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSOLDIERS del nivel 2 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSNIPERS
	TiXmlNode* tagQuantitySnipersNode = tagNivel2Node->FirstChildElement(TAG_QUANTITYSNIPERS);
	if ((tagQuantitySnipersNode)&&(tagNivel2Node->FirstChildElement(TAG_QUANTITYSNIPERS)->GetText())) {
		strQuantitySnipers.clear();
		strQuantitySnipers.append(tagNivel2Node->FirstChildElement(TAG_QUANTITYSNIPERS)->GetText());
	    if (!strQuantitySnipers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSNIPERS del nivel 2 es cero");
	    	sucess = false;
	    }

	    quantitySnipers = atoi(strQuantitySnipers.c_str());
	    if ((quantitySnipers>0)&&(quantitySnipers<1000)) {
	    	this->quantitySnipersLevel2 = quantitySnipers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SNIPERS RECHAZADA del nivel 2 " + strQuantitySnipers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSOLDIERS del nivel 2 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYGUNNERS
	TiXmlNode* tagQuantityGunnersNode = tagNivel2Node->FirstChildElement(TAG_QUANTITYGUNNERS);
	if ((tagQuantityGunnersNode)&&(tagNivel2Node->FirstChildElement(TAG_QUANTITYGUNNERS)->GetText())) {
		strQuantityGunners.clear();
		strQuantityGunners.append(tagNivel2Node->FirstChildElement(TAG_QUANTITYGUNNERS)->GetText());
	    if (!strQuantityGunners.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYGUNNERS del nivel 2 es cero");
	    	sucess = false;
	    }

	    quantityGunners = atoi(strQuantityGunners.c_str());
	    if ((quantityGunners>0)&&(quantityGunners<1000)) {
	    	this->quantityGunnersLevel2 = quantityGunners;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE GUNNERS RECHAZADA del nivel 2: " + strQuantityGunners);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYGUNNERS del nivel 2 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSCUBASOLDIERS
	TiXmlNode* tagQuantityScubaSoldiersNode = tagNivel2Node->FirstChildElement(TAG_QUANTITYSCUBASOLDIERS);
	if ((tagQuantityScubaSoldiersNode)&&(tagNivel2Node->FirstChildElement(TAG_QUANTITYSCUBASOLDIERS)->GetText())) {
		strQuantityScubaSoldiers.clear();
		strQuantityScubaSoldiers.append(tagNivel2Node->FirstChildElement(TAG_QUANTITYSCUBASOLDIERS)->GetText());
	    if (!strQuantityScubaSoldiers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSCUBASOLDIERS del nivel 2 es cero");
	    	sucess = false;
	    }

	    quantityScubaSoldiers = atoi(strQuantityScubaSoldiers.c_str());
	    if ((quantityScubaSoldiers>0)&&(quantityScubaSoldiers<1000)) {
	    	this->quantityScubaSoldiersLevel2 = quantityScubaSoldiers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SCUBASOLDIERS RECHAZADA del nivel 2: " + strQuantityScubaSoldiers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSCUBASOLDIERS del nivel 2 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYWALLTURRETS
	TiXmlNode* tagQuantityWallTurretsNode = tagNivel2Node->FirstChildElement(TAG_QUANTITYWALLTURRETS);
	if ((tagQuantityWallTurretsNode)&&(tagNivel2Node->FirstChildElement(TAG_QUANTITYWALLTURRETS)->GetText())) {
		strQuantityWallTurrets.clear();
		strQuantityWallTurrets.append(tagNivel2Node->FirstChildElement(TAG_QUANTITYWALLTURRETS)->GetText());
	    if (!strQuantityWallTurrets.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYWALLTURRETS del nivel 2 es cero");
	    	sucess = false;
	    }

	    quantityWallTurrets = atoi(strQuantityWallTurrets.c_str());
	    if ((quantityWallTurrets>0)&&(quantityWallTurrets<1000)) {
	    	this->quantityWallTurretsLevel2 = quantityWallTurrets;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE WALLTURRETS RECHAZADA del nivel 2: " + strQuantityWallTurrets);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYWALLTURRETS del nivel 2 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYCANNONS
	TiXmlNode* tagQuantityCannonsNode = tagNivel2Node->FirstChildElement(TAG_QUANTITYCANNONS);
	if ((tagQuantityCannonsNode)&&(tagNivel2Node->FirstChildElement(TAG_QUANTITYCANNONS)->GetText())) {
		strQuantityCannons.clear();
		strQuantityCannons.append(tagNivel2Node->FirstChildElement(TAG_QUANTITYCANNONS)->GetText());
	    if (!strQuantityCannons.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYCANNONS del nivel 2 es cero");
	    	sucess = false;
	    }

	    quantityCannons = atoi(strQuantityCannons.c_str());
	    if ((quantityCannons>0)&&(quantityCannons<1000)) {
	    	this->quantityCannonsLevel2 = quantityCannons;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE CANNONS RECHAZADA del nivel 2: " + strQuantityCannons);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYCANNONS del nivel 2 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYFLOATERS
	TiXmlNode* tagQuantityFloatersNode = tagNivel2Node->FirstChildElement(TAG_QUANTITYFLOATERS);
	if ((tagQuantityFloatersNode)&&(tagNivel2Node->FirstChildElement(TAG_QUANTITYFLOATERS)->GetText())) {
		strQuantityFloaters.clear();
		strQuantityFloaters.append(tagNivel2Node->FirstChildElement(TAG_QUANTITYFLOATERS)->GetText());
	    if (!strQuantityFloaters.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYFLOATERS del nivel 2 es cero");
	    	sucess = false;
	    }

	    quantityFloaters = atoi(strQuantityFloaters.c_str());
	    if ((quantityFloaters>0)&&(quantityFloaters<1000)) {
	    	this->quantityFloatersLevel2 = quantityFloaters;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE FLOATERS RECHAZADA del nivel 2: " + strQuantityFloaters);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYFLOATERS del nivel 2 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSPORES
	TiXmlNode* tagQuantitySporesNode = tagNivel2Node->FirstChildElement(TAG_QUANTITYSPORES);
	if ((tagQuantitySporesNode)&&(tagNivel2Node->FirstChildElement(TAG_QUANTITYSPORES)->GetText())) {
		strQuantitySpores.clear();
		strQuantitySpores.append(tagNivel2Node->FirstChildElement(TAG_QUANTITYSPORES)->GetText());
	    if (!strQuantitySpores.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSPORES del nivel 2 es cero");
	    	sucess = false;
	    }

	    quantitySpores = atoi(strQuantitySpores.c_str());
	    if ((quantitySpores>0)&&(quantitySpores<1000)) {
	    	this->quantitySporesLevel2 = quantitySpores;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SPORES RECHAZADA del nivel 2: " + strQuantitySpores);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSPORES del nivel 2 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYCRAWLERS
	TiXmlNode* tagQuantityCrawlersNode = tagNivel2Node->FirstChildElement(TAG_QUANTITYCRAWLERS);
	if ((tagQuantityCrawlersNode)&&(tagNivel2Node->FirstChildElement(TAG_QUANTITYCRAWLERS)->GetText())) {
		strQuantityCrawlers.clear();
		strQuantityCrawlers.append(tagNivel2Node->FirstChildElement(TAG_QUANTITYCRAWLERS)->GetText());
	    if (!strQuantityCrawlers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYCRAWLERS del nivel 2 es cero");
	    	sucess = false;
	    }

	    quantityCrawlers = atoi(strQuantityCrawlers.c_str());
	    if ((quantityCrawlers>0)&&(quantityCrawlers<1000)) {
	    	this->quantityCrawlersLevel2 = quantityCrawlers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE CRAWLERS RECHAZADA del nivel 2: " + strQuantityCrawlers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYCRAWLERS del nivel 2 no existe o tiene valores invalidos");
		sucess = false;
	}

	return sucess;
}

bool GameParser::evaluateTagNivel3(){
	bool sucess = true;
	string strFondo1;
	string strFondo2;
	string strFondo3;
	string strQuantitySoldiers;
	int quantitySoldiers = 0;
	string strQuantitySnipers;
	int quantitySnipers = 0;
	string strQuantityGunners;
	int quantityGunners = 0;
	string strQuantityScubaSoldiers;
	int quantityScubaSoldiers = 0;
	string strQuantityWallTurrets;
	int quantityWallTurrets = 0;
	string strQuantityCannons;
	int quantityCannons = 0;
	string strQuantityFloaters;
	int quantityFloaters = 0;
	string strQuantitySpores;
	int quantitySpores = 0;
	string strQuantityCrawlers;
	int quantityCrawlers = 0;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);
	TiXmlNode* tagNivel3Node = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_ESCENARIOS).FirstChild(TAG_NIVEL3).ToNode();

	if (!(tagNivel3Node)){
		LOGGER_DEBUG("TAG_NIVEL3 no existe");
    	return false;
    }

    //TAG_FONDO1
	TiXmlNode* tagFondo1Node = tagNivel3Node->FirstChildElement(TAG_FONDO1);
	if ((tagFondo1Node)&&(tagNivel3Node->FirstChildElement(TAG_FONDO1)->GetText())) {
		strFondo1.clear();
		strFondo1.append(tagNivel3Node->FirstChildElement(TAG_FONDO1)->GetText());
	    if (!strFondo1.compare(VALUE_EMPTY)) {
	    	LOGGER_DEBUG("TAG_FONDO1 esta vacio");
	    	sucess = false;
	    }

        this->fondo1Nivel3 = strFondo1;
	} else {
		LOGGER_DEBUG("TAG_FONDO1 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_FONDO2
	TiXmlNode* tagFondo2Node = tagNivel3Node->FirstChildElement(TAG_FONDO2);
	if ((tagFondo2Node)&&(tagNivel3Node->FirstChildElement(TAG_FONDO2)->GetText())) {
		strFondo2.clear();
		strFondo2.append(tagNivel3Node->FirstChildElement(TAG_FONDO2)->GetText());
	    if (!strFondo2.compare(VALUE_EMPTY)) {
	    	LOGGER_DEBUG("TAG_FONDO2 esta vacio");
	    	sucess = false;
	    }
        this->fondo2Nivel3 = strFondo2;
	} else {
		LOGGER_DEBUG("TAG_FONDO2 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_FONDO3
	TiXmlNode* tagFondo3Node = tagNivel3Node->FirstChildElement(TAG_FONDO3);
	if ((tagFondo3Node)&&(tagNivel3Node->FirstChildElement(TAG_FONDO3)->GetText())) {
		strFondo3.clear();
		strFondo3.append(tagNivel3Node->FirstChildElement(TAG_FONDO3)->GetText());
	    if (!strFondo3.compare(VALUE_EMPTY)) {
	    	LOGGER_DEBUG("TAG_FONDO3 esta vacio");
	    	sucess = false;
	    }

        this->fondo3Nivel3 = strFondo3;
	} else {
		LOGGER_DEBUG("TAG_FONDO3 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSOLDIERS
	TiXmlNode* tagQuantitySoldiersNode = tagNivel3Node->FirstChildElement(TAG_QUANTITYSOLDIERS);
	if ((tagQuantitySoldiersNode)&&(tagNivel3Node->FirstChildElement(TAG_QUANTITYSOLDIERS)->GetText())) {
		strQuantitySoldiers.clear();
		strQuantitySoldiers.append(tagNivel3Node->FirstChildElement(TAG_QUANTITYSOLDIERS)->GetText());
	    if (!strQuantitySoldiers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSOLDIERS del nivel 3 es cero");
	    	sucess = false;
	    }

	    quantitySoldiers = atoi(strQuantitySoldiers.c_str());
	    if ((quantitySoldiers>0)&&(quantitySoldiers<1000)) {
	    	this->quantitySoldiersLevel3 = quantitySoldiers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SOLDIERS RECHAZADA del nivel 3: " + strQuantitySoldiers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSOLDIERS del nivel 3 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSNIPERS
	TiXmlNode* tagQuantitySnipersNode = tagNivel3Node->FirstChildElement(TAG_QUANTITYSNIPERS);
	if ((tagQuantitySnipersNode)&&(tagNivel3Node->FirstChildElement(TAG_QUANTITYSNIPERS)->GetText())) {
		strQuantitySnipers.clear();
		strQuantitySnipers.append(tagNivel3Node->FirstChildElement(TAG_QUANTITYSNIPERS)->GetText());
	    if (!strQuantitySnipers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSNIPERS del nivel 3 es cero");
	    	sucess = false;
	    }

	    quantitySnipers = atoi(strQuantitySnipers.c_str());
	    if ((quantitySnipers>0)&&(quantitySnipers<1000)) {
	    	this->quantitySnipersLevel3 = quantitySnipers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SNIPERS RECHAZADA del nivel 3 " + strQuantitySnipers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSOLDIERS del nivel 3 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYGUNNERS
	TiXmlNode* tagQuantityGunnersNode = tagNivel3Node->FirstChildElement(TAG_QUANTITYGUNNERS);
	if ((tagQuantityGunnersNode)&&(tagNivel3Node->FirstChildElement(TAG_QUANTITYGUNNERS)->GetText())) {
		strQuantityGunners.clear();
		strQuantityGunners.append(tagNivel3Node->FirstChildElement(TAG_QUANTITYGUNNERS)->GetText());
	    if (!strQuantityGunners.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYGUNNERS del nivel 3 es cero");
	    	sucess = false;
	    }

	    quantityGunners = atoi(strQuantityGunners.c_str());
	    if ((quantityGunners>0)&&(quantityGunners<1000)) {
	    	this->quantityGunnersLevel3 = quantityGunners;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE GUNNERS RECHAZADA del nivel 3: " + strQuantityGunners);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYGUNNERS del nivel 3 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSCUBASOLDIERS
	TiXmlNode* tagQuantityScubaSoldiersNode = tagNivel3Node->FirstChildElement(TAG_QUANTITYSCUBASOLDIERS);
	if ((tagQuantityScubaSoldiersNode)&&(tagNivel3Node->FirstChildElement(TAG_QUANTITYSCUBASOLDIERS)->GetText())) {
		strQuantityScubaSoldiers.clear();
		strQuantityScubaSoldiers.append(tagNivel3Node->FirstChildElement(TAG_QUANTITYSCUBASOLDIERS)->GetText());
	    if (!strQuantityScubaSoldiers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSCUBASOLDIERS del nivel 3 es cero");
	    	sucess = false;
	    }

	    quantityScubaSoldiers = atoi(strQuantityScubaSoldiers.c_str());
	    if ((quantityScubaSoldiers>0)&&(quantityScubaSoldiers<1000)) {
	    	this->quantityScubaSoldiersLevel3 = quantityScubaSoldiers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SCUBASOLDIERS RECHAZADA del nivel 3: " + strQuantityScubaSoldiers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSCUBASOLDIERS del nivel 3 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYWALLTURRETS
	TiXmlNode* tagQuantityWallTurretsNode = tagNivel3Node->FirstChildElement(TAG_QUANTITYWALLTURRETS);
	if ((tagQuantityWallTurretsNode)&&(tagNivel3Node->FirstChildElement(TAG_QUANTITYWALLTURRETS)->GetText())) {
		strQuantityWallTurrets.clear();
		strQuantityWallTurrets.append(tagNivel3Node->FirstChildElement(TAG_QUANTITYWALLTURRETS)->GetText());
	    if (!strQuantityWallTurrets.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYWALLTURRETS del nivel 3 es cero");
	    	sucess = false;
	    }

	    quantityWallTurrets = atoi(strQuantityWallTurrets.c_str());
	    if ((quantityWallTurrets>0)&&(quantityWallTurrets<1000)) {
	    	this->quantityWallTurretsLevel3 = quantityWallTurrets;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE WALLTURRETS RECHAZADA del nivel 3: " + strQuantityWallTurrets);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYWALLTURRETS del nivel 3 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYCANNONS
	TiXmlNode* tagQuantityCannonsNode = tagNivel3Node->FirstChildElement(TAG_QUANTITYCANNONS);
	if ((tagQuantityCannonsNode)&&(tagNivel3Node->FirstChildElement(TAG_QUANTITYCANNONS)->GetText())) {
		strQuantityCannons.clear();
		strQuantityCannons.append(tagNivel3Node->FirstChildElement(TAG_QUANTITYCANNONS)->GetText());
	    if (!strQuantityCannons.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYCANNONS del nivel 3 es cero");
	    	sucess = false;
	    }

	    quantityCannons = atoi(strQuantityCannons.c_str());
	    if ((quantityCannons>0)&&(quantityCannons<1000)) {
	    	this->quantityCannonsLevel3 = quantityCannons;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE CANNONS RECHAZADA del nivel 3: " + strQuantityCannons);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYCANNONS del nivel 3 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYFLOATERS
	TiXmlNode* tagQuantityFloatersNode = tagNivel3Node->FirstChildElement(TAG_QUANTITYFLOATERS);
	if ((tagQuantityFloatersNode)&&(tagNivel3Node->FirstChildElement(TAG_QUANTITYFLOATERS)->GetText())) {
		strQuantityFloaters.clear();
		strQuantityFloaters.append(tagNivel3Node->FirstChildElement(TAG_QUANTITYFLOATERS)->GetText());
	    if (!strQuantityFloaters.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYFLOATERS del nivel 3 es cero");
	    	sucess = false;
	    }

	    quantityFloaters = atoi(strQuantityFloaters.c_str());
	    if ((quantityFloaters>0)&&(quantityFloaters<1000)) {
	    	this->quantityFloatersLevel3 = quantityFloaters;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE FLOATERS RECHAZADA del nivel 3: " + strQuantityFloaters);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYFLOATERS del nivel 3 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYSPORES
	TiXmlNode* tagQuantitySporesNode = tagNivel3Node->FirstChildElement(TAG_QUANTITYSPORES);
	if ((tagQuantitySporesNode)&&(tagNivel3Node->FirstChildElement(TAG_QUANTITYSPORES)->GetText())) {
		strQuantitySpores.clear();
		strQuantitySpores.append(tagNivel3Node->FirstChildElement(TAG_QUANTITYSPORES)->GetText());
	    if (!strQuantitySpores.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYSPORES del nivel 3 es cero");
	    	sucess = false;
	    }

	    quantitySpores = atoi(strQuantitySpores.c_str());
	    if ((quantitySpores>0)&&(quantitySpores<1000)) {
	    	this->quantitySporesLevel3 = quantitySpores;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE SPORES RECHAZADA del nivel 3: " + strQuantitySpores);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYSPORES del nivel 3 no existe o tiene valores invalidos");
		sucess = false;
	}

    //TAG_QUANTITYCRAWLERS
	TiXmlNode* tagQuantityCrawlersNode = tagNivel3Node->FirstChildElement(TAG_QUANTITYCRAWLERS);
	if ((tagQuantityCrawlersNode)&&(tagNivel3Node->FirstChildElement(TAG_QUANTITYCRAWLERS)->GetText())) {
		strQuantityCrawlers.clear();
		strQuantityCrawlers.append(tagNivel3Node->FirstChildElement(TAG_QUANTITYCRAWLERS)->GetText());
	    if (!strQuantityCrawlers.compare(ZERO)) {
	    	LOGGER_DEBUG("TAG_QUANTITYCRAWLERS del nivel 3 es cero");
	    	sucess = false;
	    }

	    quantityCrawlers = atoi(strQuantityCrawlers.c_str());
	    if ((quantityCrawlers>0)&&(quantityCrawlers<1000)) {
	    	this->quantityCrawlersLevel3 = quantityCrawlers;
		}else {
			LOGGER_DEBUG("MAXIMA CANTIDAD DE CRAWLERS RECHAZADA del nivel 3: " + strQuantityCrawlers);
			sucess = false;
		}
	} else {
		LOGGER_DEBUG("TAG_QUANTITYCRAWLERS del nivel 3 no existe o tiene valores invalidos");
		sucess = false;
	}

	return sucess;
}

bool GameParser::evaluateTagPlataformas(const char * tagNivel){
	bool sucess = true;
	TiXmlNode* tagIDNode = NULL;
	TiXmlNode* tagTipoNode = NULL;
	TiXmlNode* tagXInicialNode = NULL;
	TiXmlNode* tagXFinalNode = NULL;
	TiXmlNode* tagXAlturaNode = NULL;
	string strID = ZERO;
	int id;
	string strTipo = VALUE_EMPTY;
	string strXInicial = ZERO;
	int xinicial;
	string strXFinal = ZERO;
	int xfinal;
	string strAltura = ZERO;
	int altura;

	PlataformParser plataformParser;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);
	TiXmlElement* tagPlataformElement = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_ESCENARIOS).FirstChild(tagNivel).FirstChild(TAG_PLATAFORMAS).FirstChild(TAG_PLATAFORMA).ToElement();

	for (tagPlataformElement; tagPlataformElement; tagPlataformElement = tagPlataformElement->NextSiblingElement()) {
		sucess = true;
		id = -1;
		xinicial = -1;
		xfinal = -1;
		altura = -1;

		//TAG_ID
		tagIDNode = tagPlataformElement->FirstChildElement(TAG_ID);
		if ((tagIDNode)&&(tagPlataformElement->FirstChildElement(TAG_ID)->GetText())) {
			strID.clear();
			strID.append(tagPlataformElement->FirstChildElement(TAG_ID)->GetText());
		    if (!strID.compare(ZERO)) {
		    	LOGGER_DEBUG("TAG_ID es cero");
		    	sucess = false;
		    }
		    id = atoi(strID.c_str());
		    if ((id>0)&&(id<=100000)) {
		    	plataformParser.setId(id);
			}else {
				LOGGER_DEBUG("ID DESCONOCIDO: " + strID + ", para esta plataforma");
				sucess = false;
			}
		} else {
			LOGGER_DEBUG("TAG_ID no existe o tiene valores invalidos");
			sucess = false;
		}

		//TAG_TIPO
		tagTipoNode = tagPlataformElement->FirstChildElement(TAG_TIPO);
		if ((tagTipoNode)&&(tagPlataformElement->FirstChildElement(TAG_TIPO)->GetText())) {
			strTipo.clear();
			strTipo.append(tagPlataformElement->FirstChildElement(TAG_TIPO)->GetText());
		    if (!strTipo.compare(VALUE_EMPTY)) {
		    	LOGGER_DEBUG("TAG_TIPO esta vacio");
		    	sucess = false;
		    }
			plataformParser.setTipo(strTipo);
		} else {
			LOGGER_ERROR("TAG_TIPO no existe o tiene valores invalidos");
			sucess = false;
		}

	    //TAG_XINICIAL
		tagXInicialNode = tagPlataformElement->FirstChildElement(TAG_XINICIAL);
		if ((tagXInicialNode)&&(tagPlataformElement->FirstChildElement(TAG_XINICIAL)->GetText())) {
			strXInicial.clear();
			strXInicial.append(tagPlataformElement->FirstChildElement(TAG_XINICIAL)->GetText());
		    if (!strXInicial.compare(ZERO)) {
		    	LOGGER_DEBUG("TAG_XINICIAL es cero");
		    	sucess = false;
		    }
		    xinicial = atoi(strXInicial.c_str());
		    if ((xinicial>0)&&(xinicial<=100000)) {
		    	plataformParser.setXInicial(xinicial);
			}else {
				LOGGER_ERROR("XINICIAL DESCONOCIDO: " + strXInicial + ", su id de plataforma es: " + strID);
				sucess = false;
			}
		} else {
			LOGGER_ERROR("TAG_XINICIAL no existe o tiene valores invalidos");
			sucess = false;
		}

	    //TAG_XFINAL
		tagXFinalNode = tagPlataformElement->FirstChildElement(TAG_XFINAL);
		if ((tagXFinalNode)&&(tagPlataformElement->FirstChildElement(TAG_XFINAL)->GetText())) {
			strXFinal.clear();
			strXFinal.append(tagPlataformElement->FirstChildElement(TAG_XFINAL)->GetText());
		    if (!strXFinal.compare(ZERO)) {
		    	LOGGER_DEBUG("TAG_XFINAL es cero");
		    	sucess = false;
		    }
		    xfinal = atoi(strXFinal.c_str());
		    if ((xfinal>0)&&(xfinal<=100000)) {
		    	if (xfinal>xinicial) {
		    		plataformParser.setXFinal(xfinal);
				}else{
					LOGGER_DEBUG("XFINAL NO ES MAYOR QUE XINICIAL: " + strXFinal + ", su id de plataforma es: " + strID);
					sucess = false;
				}
			}else {
				LOGGER_DEBUG("XFINAL DESCONOCIDO: " + strXFinal + ", su id de plataforma es: " + strID);
				sucess = false;
			}
		} else {
			LOGGER_DEBUG("TAG_XFINAL no existe o tiene valores invalidos");
			sucess = false;
		}

	    //TAG_ALTURA
		tagXAlturaNode = tagPlataformElement->FirstChildElement(TAG_ALTURA);
		if ((tagXAlturaNode)&&(tagPlataformElement->FirstChildElement(TAG_ALTURA)->GetText())) {
			strAltura.clear();
			strAltura.append(tagPlataformElement->FirstChildElement(TAG_ALTURA)->GetText());
		    if (!strAltura.compare(ZERO)) {
		    	LOGGER_DEBUG("TAG_ALTURA es cero");
		    	sucess = false;
		    }
		    altura = atoi(strAltura.c_str());
		    if ((altura>0)&&(altura<=100000)) {
		    	plataformParser.setAltura(altura);
			}else {
				LOGGER_DEBUG("ALTURA DESCONOCIDA: " + strAltura + ", su id de plataforma es: " + strID);
				sucess = false;
			}
		    plataformParser.setAltura(atoi(strAltura.c_str()));
		} else {
			LOGGER_DEBUG("TAG_ALTURA no existe o tiene valores invalidos");
			sucess = false;
		}

		if (sucess) {
			if (tagNivel==TAG_NIVEL1){
				this->plataformas.push_back(plataformParser);
				LOGGER_DEBUG("Se ha cargado exitosamente la plataforma cuyo ID es: " + strID);
				LOGGER_DEBUG("Esta plataforma es de tipo: " + strTipo);
				LOGGER_DEBUG("Esta plataforma tiene xinicial: " + strXInicial);
				LOGGER_DEBUG("Esta plataforma tiene xfinal: " + strXFinal);
				LOGGER_DEBUG("Esta plataforma tiene altura: " + strAltura);
			}
			if (tagNivel==TAG_NIVEL2){
				this->plataforms2.push_back(plataformParser);
				LOGGER_DEBUG("Se ha cargado exitosamente la plataforma cuyo ID es: " + strID);
				LOGGER_DEBUG("Esta plataforma es de tipo: " + strTipo);
				LOGGER_DEBUG("Esta plataforma tiene xinicial: " + strXInicial);
				LOGGER_DEBUG("Esta plataforma tiene xfinal: " + strXFinal);
				LOGGER_DEBUG("Esta plataforma tiene altura: " + strAltura);
			}
			if (tagNivel==TAG_NIVEL3){
				this->plataforms3.push_back(plataformParser);
				LOGGER_DEBUG("Se ha cargado exitosamente la plataforma cuyo ID es: " + strID);
				LOGGER_DEBUG("Esta plataforma es de tipo: " + strTipo);
				LOGGER_DEBUG("Esta plataforma tiene xinicial: " + strXInicial);
				LOGGER_DEBUG("Esta plataforma tiene xfinal: " + strXFinal);
				LOGGER_DEBUG("Esta plataforma tiene altura: " + strAltura);
			}
		}
	}

	return sucess;
}

bool GameParser::evaluateTagItems(const char * tagNivel){
	bool sucess = true;
	TiXmlNode* tagIDNode = NULL;
	TiXmlNode* tagTipoNode = NULL;
	TiXmlNode* tagXPosNode = NULL;
	TiXmlNode* tagYPosNode = NULL;
	string strID = ZERO;
	int id;
	string strTipo = VALUE_EMPTY;
	string strXPos = ZERO;
	int x_pos;
	string strYPos = ZERO;
	int y_pos;

	ItemParser itemParser;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);
	TiXmlElement* tagItemElement = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_ESCENARIOS).FirstChild(tagNivel).FirstChild(TAG_ITEMS).FirstChild(TAG_ITEM).ToElement();

	for (tagItemElement; tagItemElement; tagItemElement = tagItemElement->NextSiblingElement()) {
		sucess = true;
		id = -1;
		x_pos = -1;
		y_pos = -1;

		//TAG_ID
		tagIDNode = tagItemElement->FirstChildElement(TAG_ID);
		if ((tagIDNode)&&(tagItemElement->FirstChildElement(TAG_ID)->GetText())) {
			strID.clear();
			strID.append(tagItemElement->FirstChildElement(TAG_ID)->GetText());
		    if (!strID.compare(ZERO)) {
		    	LOGGER_DEBUG("TAG_ID es cero");
		    	sucess = false;
		    }
		    id = atoi(strID.c_str());
		    if ((id>0)&&(id<=100000)) {
		    	itemParser.setId(id);
			}else {
				LOGGER_DEBUG("ID DESCONOCIDO: " + strID + ", para este item");
				sucess = false;
			}
		} else {
			LOGGER_DEBUG("TAG_ID no existe o tiene valores invalidos");
			sucess = false;
		}

		//TAG_TIPO
		tagTipoNode = tagItemElement->FirstChildElement(TAG_TIPO);
		if ((tagTipoNode)&&(tagItemElement->FirstChildElement(TAG_TIPO)->GetText())) {
			strTipo.clear();
			strTipo.append(tagItemElement->FirstChildElement(TAG_TIPO)->GetText());
		    if (!strTipo.compare(VALUE_EMPTY)) {
		    	LOGGER_DEBUG("TAG_TIPO esta vacio");
		    	sucess = false;
		    }
			itemParser.setTipo(strTipo);
		} else {
			LOGGER_ERROR("TAG_TIPO no existe o tiene valores invalidos");
			sucess = false;
		}

	    //TAG_XPOS
		tagXPosNode = tagItemElement->FirstChildElement(TAG_XPOS);
		if ((tagXPosNode)&&(tagItemElement->FirstChildElement(TAG_XPOS)->GetText())) {
			strXPos.clear();
			strXPos.append(tagItemElement->FirstChildElement(TAG_XPOS)->GetText());
		    if (!strXPos.compare(ZERO)) {
		    	LOGGER_DEBUG("TAG_XPOS es cero");
		    	sucess = false;
		    }
		    x_pos = atoi(strXPos.c_str());
		    if ((x_pos>0)&&(x_pos<=100000)) {
		    	itemParser.setPosX(x_pos);
			}else {
				LOGGER_ERROR("XPOS DESCONOCIDO: " + strXPos + ", su id de item es: " + strID);
				sucess = false;
			}
		} else {
			LOGGER_ERROR("TAG_XPOS no existe o tiene valores invalidos");
			sucess = false;
		}

	    //TAG_YPOS
		tagYPosNode = tagItemElement->FirstChildElement(TAG_YPOS);
		if ((tagYPosNode)&&(tagItemElement->FirstChildElement(TAG_YPOS)->GetText())) {
			strYPos.clear();
			strYPos.append(tagItemElement->FirstChildElement(TAG_YPOS)->GetText());
		    if (!strYPos.compare(ZERO)) {
		    	LOGGER_DEBUG("TAG_YPOS es cero");
		    	sucess = false;
		    }
		    y_pos = atoi(strYPos.c_str());
		    if ((y_pos>0)&&(y_pos<=100000)) {
	    		itemParser.setPosY(y_pos);
			}else {
				LOGGER_DEBUG("YPOS DESCONOCIDO: " + strYPos + ", su id de item es: " + strID);
				sucess = false;
			}
		} else {
			LOGGER_DEBUG("TAG_YPOS no existe o tiene valores invalidos");
			sucess = false;
		}

		if (sucess) {
			if (tagNivel==TAG_NIVEL1){
				this->items1.push_back(itemParser);
				LOGGER_DEBUG("Se ha cargado exitosamente el item cuyo ID es: " + strID);
				LOGGER_DEBUG("Este item es de tipo: " + strTipo);
				LOGGER_DEBUG("Este item tiene x_pos: " + strXPos);
				LOGGER_DEBUG("Este item tiene y_pos: " + strYPos);
			}
			if (tagNivel==TAG_NIVEL2){
				this->items2.push_back(itemParser);
				LOGGER_DEBUG("Se ha cargado exitosamente el item cuyo ID es: " + strID);
				LOGGER_DEBUG("Este item es de tipo: " + strTipo);
				LOGGER_DEBUG("Este item tiene x_pos: " + strXPos);
				LOGGER_DEBUG("Este item tiene y_pos: " + strYPos);
			}
			if (tagNivel==TAG_NIVEL3){
				this->items3.push_back(itemParser);
				LOGGER_DEBUG("Se ha cargado exitosamente el item cuyo ID es: " + strID);
				LOGGER_DEBUG("Este item es de tipo: " + strTipo);
				LOGGER_DEBUG("Este item tiene x_pos: " + strXPos);
				LOGGER_DEBUG("Este item tiene y_pos: " + strYPos);
			}
		}
	}

	return sucess;
}

bool GameParser::evaluateDataXML (){
	bool sucess = true;

	TiXmlHandle tiXmlHandle(this->tiXmlFileConfig);

	sucess = this->evaluateTagDebug();
	if (sucess) {
		LOGGER_DEBUG("TAG_DEBUG, evaluacion aprobada");
	}

	sucess = this->evaluateTagNivel1();
	if (sucess) {
		LOGGER_DEBUG("TAG_NIVEL1, evaluacion aprobada");
	}

	TiXmlNode* tagPlataforma = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_ESCENARIOS).FirstChild(TAG_NIVEL1).FirstChild(TAG_PLATAFORMAS).FirstChild(TAG_PLATAFORMA).ToNode();
	if (tagPlataforma) {
		sucess = this->evaluateTagPlataformas(TAG_NIVEL1);
		if (sucess) {
			LOGGER_DEBUG("TAG_PLATAFORMAS del nivel 1, evaluacion aprobada");
		}
	} else {
		LOGGER_DEBUG("TAG_PLATAFORMAS del nivel 1 no existe");
    	return false;
	}

	TiXmlNode* tagItem1 = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_ESCENARIOS).FirstChild(TAG_NIVEL1).FirstChild(TAG_ITEMS).FirstChild(TAG_ITEM).ToNode();
	if (tagItem1) {
		sucess = this->evaluateTagItems(TAG_NIVEL1);
		if (sucess) {
			LOGGER_DEBUG("TAG_ITEMS del nivel 1, evaluacion aprobada");
		}
	} else {
		LOGGER_DEBUG("TAG_ITEMS del nivel 1 no existe");
    	return false;
	}

	sucess = this->evaluateTagNivel2();
	if (sucess) {
		LOGGER_DEBUG("TAG_NIVEL2, evaluacion aprobada");
	}

	TiXmlNode* tagPlataforma2 = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_ESCENARIOS).FirstChild(TAG_NIVEL2).FirstChild(TAG_PLATAFORMAS).FirstChild(TAG_PLATAFORMA).ToNode();
	if (tagPlataforma2) {
		sucess = this->evaluateTagPlataformas(TAG_NIVEL2);
		if (sucess) {
			LOGGER_DEBUG("TAG_PLATAFORMAS del nivel 2, evaluacion aprobada");
		}
	} else {
		LOGGER_DEBUG("TAG_PLATAFORMAS del nivel 2 no existe");
    	return false;
	}

	TiXmlNode* tagItem2 = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_ESCENARIOS).FirstChild(TAG_NIVEL2).FirstChild(TAG_ITEMS).FirstChild(TAG_ITEM).ToNode();
	if (tagItem2) {
		sucess = this->evaluateTagItems(TAG_NIVEL2);
		if (sucess) {
			LOGGER_DEBUG("TAG_ITEMS del nivel 2, evaluacion aprobada");
		}
	} else {
		LOGGER_DEBUG("TAG_ITEMS del nivel 2 no existe");
    	return false;
	}

	sucess = this->evaluateTagNivel3();
	if (sucess) {
		LOGGER_DEBUG("TAG_NIVEL3, evaluacion aprobada");
	}

	TiXmlNode* tagPlataforma3 = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_ESCENARIOS).FirstChild(TAG_NIVEL3).FirstChild(TAG_PLATAFORMAS).FirstChild(TAG_PLATAFORMA).ToNode();
	if (tagPlataforma3) {
		sucess = this->evaluateTagPlataformas(TAG_NIVEL3);
		if (sucess) {
			LOGGER_DEBUG("TAG_PLATAFORMAS del nivel 3, evaluacion aprobada");
		}
	} else {
		LOGGER_DEBUG("TAG_PLATAFORMAS  del nivel 3 no existe");
    	return false;
	}

	TiXmlNode* tagItem3 = tiXmlHandle.FirstChild(TAG_CONFIGURATION).FirstChild(TAG_ESCENARIOS).FirstChild(TAG_NIVEL3).FirstChild(TAG_ITEMS).FirstChild(TAG_ITEM).ToNode();
	if (tagItem3) {
		sucess = this->evaluateTagItems(TAG_NIVEL3);
		if (sucess) {
			LOGGER_DEBUG("TAG_ITEMS del nivel 3, evaluacion aprobada");
		}
	} else {
		LOGGER_DEBUG("TAG_ITEMS del nivel 3 no existe");
    	return false;
	}

	return sucess;
}

bool GameParser::loadConfiguration() {
	bool sucess = true;

	this->tiXmlFileConfig = new TiXmlDocument (Constants::FILE_CONFIGURATION);
	if (this->tiXmlFileConfig->LoadFile()) {
		this->fileConfigLoaded = true;
		evaluateDataXML();
	} else {
		this->tiXmlDefaultFileConfig = new TiXmlDocument (Constants::DEFAULT_FILE_CONFIGURATION);
		if (this->tiXmlDefaultFileConfig->LoadFile()) {
			this->tiXmlFileConfig = this->tiXmlDefaultFileConfig;
			this->defaultfileConfigLoaded = true;
			evaluateDataXML();
		} else {
			LOGGER_ERROR("No hay archivos de configuracion");
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

GameParser::~GameParser() {
	// TODO Auto-generated destructor stub
	if (this->tiXmlFileConfig) {
		delete this->tiXmlFileConfig;
		this->fileConfigLoaded = false;
	}
	if (this->tiXmlDefaultFileConfig) {
		delete this->tiXmlDefaultFileConfig;
		this->defaultfileConfigLoaded = false;
	}
}

const string& GameParser::getFondo1Nivel1() const {
	return fondo1Nivel1;
}

const string& GameParser::getFondo1Nivel2() const {
	return fondo1Nivel2;
}

const string& GameParser::getFondo1Nivel3() const {
	return fondo1Nivel3;
}

const string& GameParser::getFondo2Nivel1() const {
	return fondo2Nivel1;
}

const string& GameParser::getFondo2Nivel2() const {
	return fondo2Nivel2;
}

const string& GameParser::getFondo2Nivel3() const {
	return fondo2Nivel3;
}

const string& GameParser::getFondo3Nivel1() const {
	return fondo3Nivel1;
}

const string& GameParser::getFondo3Nivel2() const {
	return fondo3Nivel2;
}

const string& GameParser::getFondo3Nivel3() const {
	return fondo3Nivel3;
}

const string& GameParser::getLevel() const {
	return level;
}

int GameParser::getQuantityEnemiesLevel1() {
	int totalEnemies = 0;
	totalEnemies = this->getQuantityCannonsLevel1()+this->getQuantityCrawlersLevel1()+this->getQuantityFloatersLevel1()+
				   this->getQuantityGunnersLevel1()+this->getQuantityScubaSoldiersLevel1()+this->getQuantitySnipersLevel1()+
				   this->getQuantitySoldiersLevel1()+this->getQuantitySporesLevel1()+this->getQuantityWallTurretsLevel1();
	this->quantityEnemiesLevel1 = totalEnemies+1;//Tomando en cuenta al BOSS del nivel 1.
	return quantityEnemiesLevel1;
}

int GameParser::getQuantityEnemiesLevel2(){
	int totalEnemies = 0;
	totalEnemies = this->getQuantityCannonsLevel2()+this->getQuantityCrawlersLevel2()+this->getQuantityFloatersLevel2()+
				   this->getQuantityGunnersLevel2()+this->getQuantityScubaSoldiersLevel2()+this->getQuantitySnipersLevel2()+
				   this->getQuantitySoldiersLevel2()+this->getQuantitySporesLevel2()+this->getQuantityWallTurretsLevel2();
	this->quantityEnemiesLevel2 = totalEnemies+1;//Tomando en cuenta al BOSS del nivel 2.
	return quantityEnemiesLevel2;
}

int GameParser::getQuantityEnemiesLevel3(){
	int totalEnemies = 0;
	totalEnemies = this->getQuantityCannonsLevel3()+this->getQuantityCrawlersLevel3()+this->getQuantityFloatersLevel3()+
				   this->getQuantityGunnersLevel3()+this->getQuantityScubaSoldiersLevel3()+this->getQuantitySnipersLevel3()+
				   this->getQuantitySoldiersLevel3()+this->getQuantitySporesLevel3()+this->getQuantityWallTurretsLevel3();
	this->quantityEnemiesLevel3 = totalEnemies+1;//Tomando en cuenta al BOSS del nivel 3.
	return quantityEnemiesLevel3;
}

const std::list<PlataformParser>& GameParser::getPlatforms1() const {
	return plataformas;
}

const std::list<PlataformParser>& GameParser::getPlatforms2() const {
	return plataforms2;
}

const std::list<PlataformParser>& GameParser::getPlatforms3() const {
	return plataforms3;
}

const std::list<ItemParser>& GameParser::getItems1() const {
	return items1;
}

const std::list<ItemParser>& GameParser::getItems2() const {
	return items2;
}

const std::list<ItemParser>& GameParser::getItems3() const {
	return items3;
}

int GameParser::getQuantityCannonsLevel1() const {
	return quantityCannonsLevel1;
}

int GameParser::getQuantityCannonsLevel2() const {
	return quantityCannonsLevel2;
}

int GameParser::getQuantityCannonsLevel3() const {
	return quantityCannonsLevel3;
}

int GameParser::getQuantityCrawlersLevel1() const {
	return quantityCrawlersLevel1;
}

int GameParser::getQuantityCrawlersLevel2() const {
	return quantityCrawlersLevel2;
}

int GameParser::getQuantityCrawlersLevel3() const {
	return quantityCrawlersLevel3;
}

int GameParser::getQuantityFloatersLevel1() const {
	return quantityFloatersLevel1;
}

int GameParser::getQuantityFloatersLevel2() const {
	return quantityFloatersLevel2;
}

int GameParser::getQuantityFloatersLevel3() const {
	return quantityFloatersLevel3;
}

int GameParser::getQuantityGunnersLevel1() const {
	return quantityGunnersLevel1;
}

int GameParser::getQuantityGunnersLevel2() const {
	return quantityGunnersLevel2;
}

int GameParser::getQuantityGunnersLevel3() const {
	return quantityGunnersLevel3;
}

int GameParser::getQuantityScubaSoldiersLevel1() const {
	return quantityScubaSoldiersLevel1;
}

int GameParser::getQuantityScubaSoldiersLevel2() const {
	return quantityScubaSoldiersLevel2;
}

int GameParser::getQuantityScubaSoldiersLevel3() const {
	return quantityScubaSoldiersLevel3;
}

int GameParser::getQuantitySnipersLevel1() const {
	return quantitySnipersLevel1;
}

int GameParser::getQuantitySnipersLevel2() const {
	return quantitySnipersLevel2;
}

int GameParser::getQuantitySnipersLevel3() const {
	return quantitySnipersLevel3;
}

int GameParser::getQuantitySoldiersLevel1() const {
	return quantitySoldiersLevel1;
}

int GameParser::getQuantitySoldiersLevel2() const {
	return quantitySoldiersLevel2;
}

int GameParser::getQuantitySoldiersLevel3() const {
	return quantitySoldiersLevel3;
}

int GameParser::getQuantitySporesLevel1() const {
	return quantitySporesLevel1;
}

int GameParser::getQuantitySporesLevel2() const {
	return quantitySporesLevel2;
}

int GameParser::getQuantitySporesLevel3() const {
	return quantitySporesLevel3;
}

int GameParser::getQuantityWallTurretsLevel1() const {
	return quantityWallTurretsLevel1;
}

int GameParser::getQuantityWallTurretsLevel2() const {
	return quantityWallTurretsLevel2;
}

int GameParser::getQuantityWallTurretsLevel3() const {
	return quantityWallTurretsLevel3;
}
