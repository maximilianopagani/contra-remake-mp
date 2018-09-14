/*
 * KeyEventHandler.h
 *
 *  Created on: Sep 14, 2018
 *      Author: giova
 */
#include "SDL2/SDL.h"

#ifndef KEYEVENTHANDLER_H_
#define KEYEVENTHANDLER_H_

class KeyEventHandler {
public:
	KeyEventHandler();

	void setState(SDL_Keycode key, bool state){
			keyState[key]=state;
		}
	bool getState(SDL_Keycode key){
			return keyState[key];
		}
	void clean(){
		for(int i =0 ; i < 255 ;i++){
			keyState[i]=false ;
		}
	}
private:
	bool keyState[255];
};

#endif /* KEYEVENTHANDLER_H_ */
