/*
 * ItemParser.hh
 *
 *  Created on: Nov 4, 2018
 *      Author: gmc
 */

#ifndef UTILS_ITEMPARSER_HH_
#define UTILS_ITEMPARSER_HH_

#include <string>

using namespace std;

class ItemParser {
private:
	int id;
	string tipo;
	int x_pos;
	int y_pos;

public:
	ItemParser();
	int getId() const;
	const string& getTipo() const;
	int getPosX() const;
	int getPosY() const;
	void setId(int id);
	void setTipo(const string& tipo);
	void setPosX(int posX);
	void setPosY(int posY);
	virtual ~ItemParser();
};

#endif /* UTILS_ITEMPARSER_HH_ */
