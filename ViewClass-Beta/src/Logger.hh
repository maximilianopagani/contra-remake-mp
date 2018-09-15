//============================================================================
// Name        : Logger.hh
// Author      : pola17
//============================================================================

#include <fstream>
#include <string>

// MACROS -- USE MACROS
//------------------------------------------------------------
//#define LOGGER_INIT(LEVEL, FILE) Logger::init(LEVEL, FILE);
#define LOGGER_INIT(LEVEL) Logger::init(LEVEL, "logs/" + Utils::getDate() + "_log.txt");
#define LOGGER_INIT_FILELESS(LEVEL) Logger::init(LEVEL, "");
#define LOGGER_ERROR(MSG) Logger::logs(Logger::ERROR,MSG);
#define LOGGER_INFO(MSG) Logger::logs(Logger::INFO,MSG);
#define LOGGER_DEBUG(MSG) Logger::logs(Logger::Level::DEBUG,MSG);
#define LOGGER_KILL() Logger::kill();
//------------------------------------------------------------

using namespace std;

class Logger
{
public:
    enum Level {DEBUG, INFO, ERROR, OFF};

    // logFile == "" to write in standard output
    static void init(Level level, const string& logFile);
    static void logs(Level level, const string& message);
    static void kill();

private:
    bool active;
    ofstream fileStream;
    Level level;

    // instance of Logger (singleton style)
    static Logger instance;
    static const string LEVEL_NAMES[];
    static void logs(const string& level, const string& message);
};