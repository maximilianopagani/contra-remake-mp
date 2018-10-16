/*
 * UserParser.hh
 *
 *  Created on: Oct 2, 2018
 *      Author: gmc
 */

#ifndef SERVER_USERPARSER_HH_
#define SERVER_USERPARSER_HH_

#include <string>
#include "ServerConstants.hh"

using namespace std;

class UserParser {
private:
	int id;
	string name;
	string password;

public:
	UserParser();
	virtual ~UserParser();
	int getId() const;
	void setId(int id);
	const string& getName() const;
	void setName(const string& name);
	const string& getPassword() const;
	void setPassword(const string& password);
};

#endif /* SERVER_USERPARSER_HH_ */
