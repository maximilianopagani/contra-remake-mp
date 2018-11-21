/*
 * Sound.hh
 *
 *  Created on: Nov 2, 2018
 *      Author: giova
 */

#ifndef CLIENT_SOUND_SOUND_HH_
#define CLIENT_SOUND_SOUND_HH_

#include <SDL2/SDL_mixer.h>
#include "../../Utils/Logger.hh"

enum Music_Types {
		LOGIN_BACKGROUND,
		LEVEL1_BACKGROUND,
		LEVEL2_BACKGROUND,
		LEVEL3_BACKGROUND,
		STAGE_CLEAR,
		BOSS_BASE,
		BULLET_1
};

class Sound {
public:
	Sound();
	virtual ~Sound();

	void play(int type, int subtype , int loops , int volumen);
	void stopMusic();

	void destroy();

private:
	Mix_Music* musicLogin;
	Mix_Music* musicLevel1;
	Mix_Music* musicLevel2;
	Mix_Music* musicLevel3;
	Mix_Music* gameover;
	Mix_Music* stageclear;
	Mix_Music* boss;

	Mix_Chunk* bullet1;
	Mix_Chunk* bullet2;
	Mix_Chunk* bullet3;
	Mix_Chunk* item;
	Mix_Chunk* dead;
	Mix_Chunk* enemy_dead;
};

#endif /* CLIENT_SOUND_SOUND_HH_ */
