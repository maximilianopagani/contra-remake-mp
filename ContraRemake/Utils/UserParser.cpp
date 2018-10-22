/*
 * UserParser.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: gmc
 */

#include "UserParser.hh"


UserParser::UserParser() {
	// TODO Auto-generated constructor stub
	this->id = 0;
	this->name = VALUE_EMPTY;
	this->password = VALUE_EMPTY;
}

UserParser::~UserParser() {
	// TODO Auto-generated destructor stub
}

int UserParser::getId() const {
	return id;
}

void UserParser::setId(int id) {
	this->id = id;
}

const string& UserParser::getName() const {
	return name;
}

void UserParser::setName(const string& name) {
	this->name = name;
}

const string& UserParser::getPassword() const {
	return password;
}

void UserParser::setPassword(const string& password) {
	this->password = password;
}
