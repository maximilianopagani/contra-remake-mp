//============================================================================
// Name        : Utils.cpp
// Author      : pola17
//============================================================================

#include "Utils.hh"

// get current time, format YYYY-MM-DD.HH:mm:ss
const string Utils::getTimestamp()
{
    time_t currentTime = time(0);
    char buf[80];
    struct tm tstruct = *localtime(&currentTime);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

// get current date, format YYYY-MM-DD
const string Utils::getDate()
{
    time_t currentTime = time(0);
    char buf[80];
    struct tm tstruct = *localtime(&currentTime);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return buf;
}

const string Utils::toUppercase(string aString)
{
    std::transform(aString.begin(), aString.end(), aString.begin(),
                   [](unsigned char c) -> unsigned char { return std::toupper(c); });
	return aString;
}
