#include <iostream>

#include "Client/src/ClientMain.hh"
//#include "Utils/Logger.hh"
#include "Server/src/Model/ServerMain.hh"

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
	//Logger::Level logMode;
	bool hasLogMode = true;

	if(argc == 1)
	{
		print_usage();
	}
	else if(argc >= 3)
	{
		if(std::string(argv[1]) == "-mode")
		{
			if(std::string(argv[2]) == "CLIENT" || std::string(argv[2]) == "client")
			{
				ClientMain();
			}
			else if(std::string(argv[2]) == "SERVER" || std::string(argv[2]) == "server")
			{
				ServerMain(argc, argv);
			}
			else
			{
				print_usage();
			}
		}
		else
		{
			print_usage();
		}
		/*
		if (argc >= 4) {
			if (std::string(argv[3]) != "-logger_mode") {
				hasLogMode = false;
				std::cerr << "Usage: " << argv[0] << " -logger_mode LOGGER_MODE" << std::endl;
				std::cerr << "Logger mode will be defined from configuration file" << std::endl;
			} else {
				string arg2 = Utils::toUppercase(string(argv[2]));
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

			if (!hasLogMode) {
				std::cerr << "Setup default mode is ERROR" << std::endl;
				LOGGER_INIT_SETUP(Logger::ERROR);
			} else
				LOGGER_INIT_SETUP(logMode);
		}
		*/

	}
	return 0;
} 
