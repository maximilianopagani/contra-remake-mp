/*
 * Sound.cpp
 *
 *  Created on: Nov 2, 2018
 *      Author: giova
 */

#include "Sound.hh"

Sound::Sound() {

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 8192) < 0){
			LOGGER_ERROR("Falló al iniciar SDL_Mixer");
	}

	musicLogin = Mix_LoadMUS("../Sonidos/musica/login.mp3");
	musicLevel1= Mix_LoadMUS("../Sonidos/musica/Stage1.mp3");
	musicLevel2= Mix_LoadMUS("../Sonidos/musica/Stage2.mp3");
	musicLevel3= Mix_LoadMUS("../Sonidos/musica/Stage3.mp3");
	gameover= Mix_LoadMUS("../Sonidos/musica/gameOver.mp3");
	stageclear= Mix_LoadMUS("../Sonidos/musica/stageclear.mp3");
	boss= Mix_LoadMUS("../Sonidos/musica/boss.mp3");

	item= Mix_LoadWAV("../Sonidos/effects/item.wav");

	dead =  Mix_LoadWAV("../Sonidos/player/dead.wav");

	enemy_dead =  Mix_LoadWAV("../Sonidos/enemys/enemyDead.wav");

	bullet1 = Mix_LoadWAV("../Sonidos/bullet/bulletNormal.wav");
	bullet2 = Mix_LoadWAV("../Sonidos/bullet/bulletTriple.wav");
	bullet3 = Mix_LoadWAV("../Sonidos/bullet/hadoken.wav");

}

void Sound::play(int type, int subtype , int loops , int volumen){

	switch(type){

		case 0:{

				if(subtype == 0){
					Mix_PlayMusic(musicLogin,-1);
					Mix_VolumeMusic(volumen-20);
				}
				if(subtype == 1){
					Mix_PlayMusic(musicLevel1,-1);
					Mix_VolumeMusic(volumen-20);
				}
				if(subtype == 2){
					Mix_PlayMusic(musicLevel2,-1);
					Mix_VolumeMusic(volumen-20);
				}
				if(subtype == 3){
					Mix_PlayMusic(musicLevel3,-1);
					Mix_VolumeMusic(volumen+10);
				}

					break;
			}

		case 1:{
					if(subtype == 0){
						Mix_PlayChannel(2,item,loops);
						Mix_VolumeChunk(item, volumen-10);
					}
					if(subtype == 1){
						Mix_HaltMusic();
						Mix_PlayMusic(gameover,0);
						Mix_VolumeMusic(volumen-10);
					}
					if(subtype == 2){
						Mix_HaltMusic();
						Mix_PlayMusic(stageclear,0);
						Mix_VolumeMusic(volumen);
					}
					if(subtype == 3){
						Mix_HaltMusic();
						Mix_PlayMusic(boss,-1);
						Mix_VolumeMusic(volumen-20);
					}

					break;
			}

		case 2:{
					if(subtype == 0){
						Mix_PlayChannel(4,enemy_dead, loops);
						Mix_VolumeChunk(enemy_dead, volumen-10);
					}

					break;
			}

		case 3:{
					if(subtype == 0){
						Mix_PlayChannel(2,dead, loops);
						Mix_VolumeChunk(dead, volumen+10);
					}

					break;
			}

		case 4:{
					if(subtype == 0){
						Mix_PlayChannel(3,bullet1, loops);
						Mix_VolumeChunk(bullet1, volumen-20);
					}
					if(subtype == 1){
						Mix_PlayChannel(3,bullet2, loops);
						Mix_VolumeChunk(bullet2, volumen-20);
					}
					if(subtype == 2){
						Mix_PlayChannel(3,bullet1, loops);
						Mix_VolumeChunk(bullet1, volumen-10);
					}
					if(subtype == 3){
						Mix_PlayChannel(3,bullet3, loops);
						Mix_VolumeChunk(bullet3, volumen-10);
					}

					break;
			}
		}

}


void Sound::stopMusic(){
	Mix_HaltMusic();
}

void Sound::destroy(){
	Mix_FreeMusic(musicLogin);
	Mix_FreeMusic(musicLevel1);
	Mix_FreeMusic(musicLevel2);
	Mix_FreeMusic(musicLevel3);
	Mix_FreeChunk(bullet1);
	Mix_Quit();
}

Sound::~Sound() {
	// TODO Auto-generated destructor stub
}

