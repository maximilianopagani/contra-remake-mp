//============================================================================
// Name        : Logger.hh
// Author      : pola17
//============================================================================

#ifndef SRC_LOGGER_HH_
#define SRC_LOGGER_HH_

#include <fstream>
#include <string>
#include <mutex>
#include "Utils.hh"

// MACROS -- USE MACROS
//------------------------------------------------------------
#define LOGGER_INIT(LEVEL) Logger::init(LEVEL, "logs/" + Utils::getDate() + ".log");
#define LOGGER_INIT_FILELESS(LEVEL) Logger::init(LEVEL, "");
#define LOGGER_INIT_SETUP(LEVEL) Logger::init(LEVEL, "logs/setup_" + Utils::getDate() + ".log");
#define LOGGER_ERROR(MSG) Logger::logs(Logger::ERROR, MSG, __FILE__, __LINE__);
#define LOGGER_INFO(MSG) Logger::logs(Logger::INFO, MSG, __FILE__, __LINE__);
#define LOGGER_DEBUG(MSG) Logger::logs(Logger::DEBUG, MSG, __FILE__, __LINE__);
#define LOGGER_KILL() Logger::kill();
//------------------------------------------------------------

using namespace std;

class Logger
{
public:
    enum Level {DEBUG, INFO, ERROR, OFF};

    // logFile == "" to write in standard output
    static void init(Level level, const string& logFile);
    static void logs(Level level, const string& message, const char* file, int line);
    static void kill();


private:
    bool active;
    ofstream fileStream;
    Level level;

    // instance of Logger (singleton style)
	static std::mutex logMutex;
    static Logger instance;
    static const string LEVEL_NAMES[];
    static string getFileAndLine(const char* file, int line);
    static void logs(const string& level, const string& message, const string& fileAndLine);
};
#endif /* SRC_LOGGER_HH_ */
