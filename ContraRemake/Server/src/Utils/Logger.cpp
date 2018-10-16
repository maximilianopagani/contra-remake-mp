//============================================================================
// Name        : Logger.cpp
// Author      : pola17
//============================================================================

#include "Logger.hh"

// static members initialization
// --------------------------------------
const string Logger::LEVEL_NAMES[] =
{
    "DEB",
    "INF",
    "ERR",
	"OFF"
};


Logger Logger::instance;

// function implementations
// --------------------------------------
void Logger::init(Level aLevel, const string& logFile)
{
    instance.active = true;
    instance.level = aLevel;

    if (logFile != "")
        instance.fileStream.open(logFile.c_str(), std::ofstream::app);

    logs("INI","----------------------------|MODE : " + LEVEL_NAMES[aLevel] + "|----------------------------", "");
}

void Logger::kill()
{
	logs("KLL","-------------------------------| END |-------------------------------", "");
    instance.active = false;
	instance.level = OFF;
    if(instance.fileStream.is_open())
        instance.fileStream.close();
}

string Logger::getFileAndLine(const char* file, int line)
{
	string filePath = file;
	std::size_t initial = filePath.rfind("/") + 1;
	std::size_t final = filePath.rfind(".");
	string fileName = filePath.substr(initial, final-initial);

	return fileName + ":" + to_string(line) + " || ";
}

void Logger::logs(Level aLevel, const string& message, const char* file, int line)
{
    if(instance.active && aLevel >= instance.level)
    	logs(LEVEL_NAMES[aLevel], message, getFileAndLine(file, line));
}

void Logger::logs(const string& aLevel, const string& message, const string& fileAndLine)
{
	// identify current output stream
	ostream& stream = instance.fileStream.is_open() ? instance.fileStream : std::cout;
	stream  << Utils::getTimestamp() << " <" << aLevel << "> " << fileAndLine << message << endl;
}
