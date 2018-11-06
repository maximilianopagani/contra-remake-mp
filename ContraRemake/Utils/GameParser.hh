#ifndef GAMEPARSER_HH_
#define GAMEPARSER_HH_

#include <string>
#include "../xml/tinyxml/tinyxml.h"
#include "../xml/tinyxml/tinystr.h"
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include "ServerConstants.hh"
#include "Logger.hh"
#include <list>

#include "PlatformParser.hh"
#include "ItemParser.hh"

using namespace std;

class GameParser {
private:
	//Important attributes extracted from the xml files
	string level;
	string fondo1Nivel1;
	string fondo2Nivel1;
	string fondo3Nivel1;
	string fondo1Nivel2;
	string fondo2Nivel2;
	string fondo3Nivel2;
	string fondo1Nivel3;
	string fondo2Nivel3;
	string fondo3Nivel3;

	int quantityEnemiesLevel1;
	int quantityEnemiesLevel2;
	int quantityEnemiesLevel3;

	std::list<PlataformParser> plataformas;
	std::list<PlataformParser> plataforms2;
	std::list<PlataformParser> plataforms3;

	std::list<ItemParser> items1;
	std::list<ItemParser> items2;
	std::list<ItemParser> items3;

	//Others attributes
	bool fileConfigLoaded;
	bool defaultfileConfigLoaded;
	TiXmlDocument* tiXmlFileConfig;
	TiXmlDocument* tiXmlDefaultFileConfig;
public:
	GameParser();
	bool evaluateTagDebug();
	bool evaluateTagNivel1();
	bool evaluateTagNivel2();
	bool evaluateTagNivel3();
	bool evaluateTagPlataformas(const char * tagNivel);
	bool evaluateTagItems(const char * tagNivel);
	bool evaluateTagConfiguration();
	bool evaluateDataXML();
	bool loadConfiguration();
	void testDataParserModel();

	const string& getFondo1Nivel1() const;
	const string& getFondo1Nivel2() const;
	const string& getFondo1Nivel3() const;
	const string& getFondo2Nivel1() const;
	const string& getFondo2Nivel2() const;
	const string& getFondo2Nivel3() const;
	const string& getFondo3Nivel1() const;
	const string& getFondo3Nivel2() const;
	const string& getFondo3Nivel3() const;
	const string& getLevel() const;

	std::list<PlataformParser>* getPlatforms1() { return &plataformas; }
	std::list<PlataformParser>* getPlatforms2() { return &plataforms2; }
	std::list<PlataformParser>* getPlatforms3() { return &plataforms3; }
	std::list<ItemParser>* getItems1() { return &items1; }
	std::list<ItemParser>* getItems2() { return &items2; }
	std::list<ItemParser>* getItems3() { return &items3; }

	virtual ~GameParser();
	int getQuantityEnemiesLevel1() const;
	int getQuantityEnemiesLevel2() const;
	int getQuantityEnemiesLevel3() const;
	const std::list<PlataformParser>& getPlatforms1() const;
	const std::list<PlataformParser>& getPlatforms2() const;
	const std::list<PlataformParser>& getPlatforms3() const;
	const std::list<ItemParser>& getItems1() const;
	const std::list<ItemParser>& getItems2() const;
	const std::list<ItemParser>& getItems3() const;
};

#endif /* GAMEPARSER_HH_ */
