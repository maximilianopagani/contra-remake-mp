//============================================================================
// Name        : Logger.cpp
// Author      : pola17
//============================================================================

#include "../include/Logger.hh"


// static members initialization
// --------------------------------------
const string Logger::LEVEL_NAMES[] =
{
    "DEBUG",
    "INFO ",
    "ERROR",
	" OFF "
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

    logs("INIT ","----------------------------|MODE : " + LEVEL_NAMES[aLevel] + "|----------------------------");
}

void Logger::kill()
{
    instance.active = false;
	instance.level = Level::OFF;
    if (instance.fileStream.is_open())
        instance.fileStream.close();
}

void Logger::logs(Level aLevel, const string& message)
{
    if (instance.active && aLevel >= instance.level)
    	logs(LEVEL_NAMES[aLevel], message);
}

void Logger::logs(const string& aLevel, const string& message)
{
	// identify current output stream
	ostream& stream = instance.fileStream.is_open() ? instance.fileStream : std::cout;
	stream  << "[" << Utils::getTimestamp() << "] " << "<<" << aLevel << ">>" << " || " << message << endl;
}
