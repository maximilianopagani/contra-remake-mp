/*
 * PlataformaParser.h
 *
 *  Created on: Sep 17, 2018
 *      Author: gmc
 */

#ifndef PLATAFORMPARSER_HH_
#define PLATAFORMPARSER_HH_

#include <string>
#include "../../../Utils/Constants.hh"

using namespace std;

class PlataformParser {
private:
	int id;
	string tipo;
	int x_inicial;
	int x_final;
	int altura;

public:
	PlataformParser();
	virtual ~PlataformParser();
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

#endif /* PLATAFORMPARSER_HH_ */
