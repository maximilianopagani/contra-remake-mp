#ifndef CONSTANTS_HH_
#define CONSTANTS_HH_

#include <string>

#define TAG_CONFIGURATION "configuration"
#define TAG_DEBUG "debug"
#define VALUE_EMPTY ""
#define TAG_LEVEL "level"
#define SIZE_WORD 256

#define TAG_ESCENARIOS "escenarios"

#define TAG_NIVEL1 "nivel1"
#define TAG_NIVEL2 "nivel2"
#define TAG_NIVEL3 "nivel3"

#define TAG_FONDO1 "fondo1"
#define TAG_FONDO2 "fondo2"
#define TAG_FONDO3 "fondo3"


class Constants {
public:
	static const int COUNT_STAGES;
	static const char * FILE_CONFIGURATION;
	static const char * DEFAULT_FILE_CONFIGURATION;
};

#endif /* CONSTANTS_HH_ */
