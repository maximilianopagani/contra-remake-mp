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

	int quantityRunnersLevel1;
	int quantityRiflemansLevel1;

	int quantitySoldiersLevel1;
	int quantitySnipersLevel1;
	int	quantityGunnersLevel1;
	int quantityScubaSoldiersLevel1;
	int quantityWallTurretsLevel1;
	int quantityCannonsLevel1;
	int quantityFloatersLevel1;
	int quantitySporesLevel1;
	int quantityCrawlersLevel1;


	int quantityEnemiesLevel2;

	int quantityRunnersLevel2;
	int quantityRiflemansLevel2;

	int quantitySoldiersLevel2;
	int quantitySnipersLevel2;
	int	quantityGunnersLevel2;
	int quantityScubaSoldiersLevel2;
	int quantityWallTurretsLevel2;
	int quantityCannonsLevel2;
	int quantityFloatersLevel2;
	int quantitySporesLevel2;
	int quantityCrawlersLevel2;


	int quantityEnemiesLevel3;

	int quantityRunnersLevel3;
	int quantityRiflemansLevel3;

	int quantitySoldiersLevel3;
	int quantitySnipersLevel3;
	int	quantityGunnersLevel3;
	int quantityScubaSoldiersLevel3;
	int quantityWallTurretsLevel3;
	int quantityCannonsLevel3;
	int quantityFloatersLevel3;
	int quantitySporesLevel3;
	int quantityCrawlersLevel3;


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
	int getQuantityEnemiesLevel1();
	int getQuantityEnemiesLevel2();
	int getQuantityEnemiesLevel3();
	const std::list<PlataformParser>& getPlatforms1() const;
	const std::list<PlataformParser>& getPlatforms2() const;
	const std::list<PlataformParser>& getPlatforms3() const;
	const std::list<ItemParser>& getItems1() const;
	const std::list<ItemParser>& getItems2() const;
	const std::list<ItemParser>& getItems3() const;
	int getQuantityCannonsLevel1() const;
	int getQuantityCannonsLevel2() const;
	int getQuantityCannonsLevel3() const;
	int getQuantityCrawlersLevel1() const;
	int getQuantityCrawlersLevel2() const;
	int getQuantityCrawlersLevel3() const;
	int getQuantityFloatersLevel1() const;
	int getQuantityFloatersLevel2() const;
	int getQuantityFloatersLevel3() const;
	int getQuantityGunnersLevel1() const;
	int getQuantityGunnersLevel2() const;
	int getQuantityGunnersLevel3() const;
	int getQuantityScubaSoldiersLevel1() const;
	int getQuantityScubaSoldiersLevel2() const;
	int getQuantityScubaSoldiersLevel3() const;
	int getQuantitySnipersLevel1() const;
	int getQuantitySnipersLevel2() const;
	int getQuantitySnipersLevel3() const;
	int getQuantitySoldiersLevel1() const;
	int getQuantitySoldiersLevel2() const;
	int getQuantitySoldiersLevel3() const;
	int getQuantitySporesLevel1() const;
	int getQuantitySporesLevel2() const;
	int getQuantitySporesLevel3() const;
	int getQuantityWallTurretsLevel1() const;
	int getQuantityWallTurretsLevel2() const;
	int getQuantityWallTurretsLevel3() const;
	int getQuantityRiflemansLevel1() const;
	int getQuantityRiflemansLevel2() const;
	int getQuantityRiflemansLevel3() const;
	int getQuantityRunnersLevel1() const;
	int getQuantityRunnersLevel2() const;
	int getQuantityRunnersLevel3() const;
};

#endif /* GAMEPARSER_HH_ */
