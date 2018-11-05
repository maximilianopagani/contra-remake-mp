#include <iostream>

#include "Utils/Logger.hh"
#include "Utils/GameParser.hh"
#include "Server/Model/ServerMain.hh"
#include "Client/ClientMain.hh"

using namespace std;

void print_usage()
{
	cout << "Uso: ./Contra -mode modo [-logger_mode modo]" << endl;
	cout << endl;
	cout << "Opciones:" << endl;
	cout << "-mode modo              Debe elegirse CLIENT o SERVER, según se desee." << endl;
	cout << "-logger_mode modo       Puede elegirse DEBUG, INFO o ERROR. No es obligatorio." << endl;
}

int main(int argc, char** argv) 
{ 
	Logger::Level logMode;
	bool hasLogMode = false;

	if(argc == 1)
	{
		print_usage();
	}
	// caso en que se pase un logger_mode
	else if (argc >= 4) {
		if (std::string(argv[3]) != "-logger_mode") {
			std::cerr << "Usage: " << argv[0] << " -logger_mode LOGGER_MODE" << std::endl;
			std::cerr << "Logger mode will be defined from configuration file" << std::endl;
		} else {
			hasLogMode = true;
			string arg2 = Utils::toUppercase(string(argv[4]));
			if (arg2 == "DEBUG")
				logMode = Logger::DEBUG;
			else if (arg2 == "INFO")
				logMode = Logger::INFO;
			else if (arg2 == "ERROR")
				logMode = Logger::ERROR;
			else if (arg2 == "OFF")
				logMode = Logger::OFF;
			else
			{
				hasLogMode = false;
				std::cerr << "Invalid mode: " << arg2 << std::endl;
				std::cerr << "Valid modes: [DEBUG, INFO, ERROR, OFF]" << std::endl;
				std::cerr << "Logger mode will be defined from configuration file" << std::endl;
			}
		}
	}

	if(argc >= 3)
	{
		if (!hasLogMode)
		{
			std::cerr << "Setup default mode is ERROR" << std::endl;
			LOGGER_INIT_SETUP(Logger::ERROR);
		} else
			LOGGER_INIT_SETUP(logMode);

		GameParser* parser = new GameParser();

		if (parser->loadConfiguration()) {
			LOGGER_INFO("Carga de configuracion aceptada");
			cout << "La cantidad de enemigos del nivel 1 es: " << parser->getQuantityEnemiesLevel1() << endl;
			cout << "La cantidad de enemigos del nivel 2 es: " << parser->getQuantityEnemiesLevel2() << endl;
			cout << "La cantidad de enemigos del nivel 3 es: " << parser->getQuantityEnemiesLevel3() << endl;
		} else {
			// se mata al primer logger
			LOGGER_KILL();
			if (parser)
				delete parser;
			return 1;
		}
		// se mata al primer logger
		LOGGER_KILL();

		// si no se paso por parametro, a partir del archivo de configuracion se crea el logger deseado
		if (!hasLogMode)
		{
			if (parser->getLevel() == "DEBUG") {
				LOGGER_INIT(Logger::DEBUG);
			}
			else if (parser->getLevel() == "INFO") {
				LOGGER_INIT(Logger::INFO);
			}
			else if (parser->getLevel() == "ERROR") {
				LOGGER_INIT(Logger::ERROR);
			}
			else if (parser->getLevel() == "OFF") {
				LOGGER_INIT(Logger::OFF);
			}
			else
			{
				std::cerr << "Logger mode from configuration file is invalid" << std::endl;
				std::cerr << "Logger default mode is OFF" << std::endl;
				LOGGER_INIT(Logger::OFF);
			}
		} else
			LOGGER_INIT(logMode);

		if(std::string(argv[1]) == "-mode")
		{
			if(std::string(argv[2]) == "CLIENT" || std::string(argv[2]) == "client")
				return ClientMain();
			else if(std::string(argv[2]) == "SERVER" || std::string(argv[2]) == "server")
				return ServerMain(parser); // @suppress("Invalid arguments")
			else
				print_usage();
		}
		else print_usage();
	}

	LOGGER_KILL();

	return 0;
} 
