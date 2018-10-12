/*
 * PlataformaParser.cpp
 *
 *  Created on: Sep 17, 2018
 *      Author: gmc
 */

#include "PlatformParser.hh"

PlataformParser::PlataformParser() {
	// TODO Auto-generated constructor stub
	this->id = 0;
	this->tipo = VALUE_EMPTY;
	this->x_inicial = 0;
	this->x_final = 0;
	this->altura = 0;
}

PlataformParser::~PlataformParser() {
	// TODO Auto-generated destructor stub
}

int PlataformParser::getAltura() const {
	return altura;
}

void PlataformParser::setAltura(int altura) {
	this->altura = altura;
}

int PlataformParser::getId() const {
	return id;
}

void PlataformParser::setId(int id) {
	this->id = id;
}

const string& PlataformParser::getTipo() const {
	return tipo;
}

void PlataformParser::setTipo(const string& tipo) {
	this->tipo = tipo;
}

int PlataformParser::getXFinal() const {
	return x_final;
}

void PlataformParser::setXFinal(int xFinal) {
	x_final = xFinal;
}

int PlataformParser::getXInicial() const {
	return x_inicial;
}

void PlataformParser::setXInicial(int xInicial) {
	x_inicial = xInicial;
}
