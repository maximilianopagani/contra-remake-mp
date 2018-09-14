/*
 * KeyEventHandler.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: giova
 */

#include "KeyEventHandler.h"

KeyEventHandler::KeyEventHandler() {

	for(int i =0 ; i < 255 ;i++){
		keyState[i]=1 ;
	}


}



