#ifndef CONSTANTS_HH_
#define CONSTANTS_HH_

#include <string>

#define TAG_CONFIGURATION "configuration"
#define TAG_DEBUG "debug"
#define VALUE_EMPTY ""
#define ZERO "0"
#define TAG_LEVEL "level"
#define SIZE_WORD 256

#define TAG_ESCENARIOS "escenarios"

#define TAG_NIVEL1 "nivel1"
#define TAG_NIVEL2 "nivel2"
#define TAG_NIVEL3 "nivel3"

#define TAG_FONDO1 "fondo1"
#define TAG_FONDO2 "fondo2"
#define TAG_FONDO3 "fondo3"
#define TAG_QUANTITYSOLDIERS "quantitysoldiers"
#define TAG_QUANTITYSNIPERS "quantitysnipers"
#define TAG_QUANTITYGUNNERS "quantitygunners"
#define TAG_QUANTITYSCUBASOLDIERS "quantityscubasoldiers"
#define TAG_QUANTITYWALLTURRETS "quantitywallturrets"
#define TAG_QUANTITYCANNONS "quantitycannons"
#define TAG_QUANTITYFLOATERS "quantityfloaters"
#define TAG_QUANTITYSPORES "quantityspores"
#define TAG_QUANTITYCRAWLERS "quantitycrawlers"

#define TAG_PLATAFORMAS "plataformas"
#define TAG_PLATAFORMA "plataforma"

#define TAG_ITEMS "items"
#define TAG_ITEM "item"

#define TAG_XPOS "xpos"
#define TAG_YPOS "ypos"

#define TAG_ID "id"
#define TAG_TIPO "tipo"
#define TAG_XINICIAL "xinicial"
#define TAG_XFINAL "xfinal"
#define TAG_ALTURA "altura"

/*CONSTANTES ASOCIADAS AL PARSER DEL SERVIDOR */
#define TAG_SERVER "server"
#define TAG_MAXIMUMQUANTITYCLIENTS "maximumquantityclients"
#define TAG_PORT "port"
#define TAG_USERS "users"
#define TAG_USER "user"
#define TAG_NAME "name"
#define TAG_PASSWORD "password"

/*CONSTANTES ASOCIADAS AL PARSER DEL CLIENTE*/
#define TAG_CLIENT "client"
#define TAG_CONNECTION "connection"
#define TAG_IP "ip"

class Constants {
public:
	static const int COUNT_STAGES;
	static const char * FILE_CONFIGURATION;
	static const char * DEFAULT_FILE_CONFIGURATION;
	static const char * FILE_CONFIGURATION_SERVER;
	static const char * DEFAULT_FILE_CONFIGURATION_SERVER;
};

#endif /* CONSTANTS_HH_ */
