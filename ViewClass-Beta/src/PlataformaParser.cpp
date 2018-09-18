/*
 * PlataformaParser.cpp
 *
 *  Created on: Sep 17, 2018
 *      Author: gmc
 */

#include "PlataformaParser.hh"

PlataformaParser::PlataformaParser() {
	// TODO Auto-generated constructor stub
	this->id = 0;
	this->tipo = VALUE_EMPTY;
	this->x_inicial = 0;
	this->x_final = 0;
	this->altura = 0;
}

PlataformaParser::~PlataformaParser() {
	// TODO Auto-generated destructor stub
}

int PlataformaParser::getAltura() const {
	return altura;
}

void PlataformaParser::setAltura(int altura) {
	this->altura = altura;
}

int PlataformaParser::getId() const {
	return id;
}

void PlataformaParser::setId(int id) {
	this->id = id;
}

const string& PlataformaParser::getTipo() const {
	return tipo;
}

void PlataformaParser::setTipo(const string& tipo) {
	this->tipo = tipo;
}

int PlataformaParser::getXFinal() const {
	return x_final;
}

void PlataformaParser::setXFinal(int xFinal) {
	x_final = xFinal;
}

int PlataformaParser::getXInicial() const {
	return x_inicial;
}

void PlataformaParser::setXInicial(int xInicial) {
	x_inicial = xInicial;
}
