/*
 * PlataformaParser.h
 *
 *  Created on: Sep 17, 2018
 *      Author: gmc
 */

#ifndef PLATAFORMAPARSER_HH_
#define PLATAFORMAPARSER_HH_

#include <string>
#include "Constants.hh"

using namespace std;

class PlataformaParser {
private:
	int id;
	string tipo;
	int x_inicial;
	int x_final;
	int altura;

public:
	PlataformaParser();
	virtual ~PlataformaParser();
	int getAltura() const;
	void setAltura(int altura);
	int getId() const;
	void setId(int id);
	const string& getTipo() const;
	void setTipo(const string& tipo);
	int getXFinal() const;
	void setXFinal(int xFinal);
	int getXInicial() const;
	void setXInicial(int xInicial);
};

#endif /* PLATAFORMAPARSER_HH_ */
