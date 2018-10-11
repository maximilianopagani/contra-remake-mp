/*
 * ContraRemake.hh
 *
 *  Created on: Oct 11, 2018
 *      Author: synergy
 */

#ifndef MODEL_CONTRAREMAKE_HH_
#define MODEL_CONTRAREMAKE_HH_

#include "../Vista/GameView.hh"
#include "../../../Utils/Logger.hh"
#include "../../../Utils/GameParser.hh"
#include "../../../Utils/Utils.hh"
#include "Game.hh"

class ContraRemake {
public:
	ContraRemake();
	int init(int argc, char* argv[]);
	virtual ~ContraRemake();
};

#endif /* MODEL_CONTRAREMAKE_HH_ */
