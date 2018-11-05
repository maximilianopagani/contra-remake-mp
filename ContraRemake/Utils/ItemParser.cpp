/*
 * ItemParser.cpp
 *
 *  Created on: Nov 4, 2018
 *      Author: gmc
 */

#include "ItemParser.hh"

ItemParser::ItemParser() {
	// TODO Auto-generated constructor stub
}

int ItemParser::getId() const {
	return id;
}

const string& ItemParser::getTipo() const {
	return tipo;
}

int ItemParser::getPosX() const {
	return x_pos;
}

int ItemParser::getPosY() const {
	return y_pos;
}

void ItemParser::setId(int id) {
	this->id = id;
}

void ItemParser::setTipo(const string& tipo) {
	this->tipo = tipo;
}

void ItemParser::setPosX(int posX) {
	x_pos = posX;
}

void ItemParser::setPosY(int posY) {
	y_pos = posY;
}

ItemParser::~ItemParser() {
	// TODO Auto-generated destructor stub
}
