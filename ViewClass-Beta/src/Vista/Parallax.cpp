/*
 * Parallax.cpp
 *
 *  Created on: 9 sep. 2018
 *      Author: nacho
 */

#include "Parallax.hh"
#include "../Vista/Sprite.hh"
#include "../Utils/Logger.hh"

Parallax::Parallax(GameView* _view, std::string bgPath1, std::string bgPath2, LevelNumber _level) {

    view = _view;
    level = _level;

	screenWidth = view->getWindowWidth();
	screenHeight = view->getWindowHeight();
	screenPosX = 0;
	screenPosY = 0;

	LOGGER_INFO("Parallax: Inicio creación de sprites");
	bgSprite1 = new Sprite(view, bgPath1, 1920, 1080, screenWidth, screenHeight);
    bgSprite2 = new Sprite(view, bgPath2, 1920, 1080, screenWidth, screenHeight);
    LOGGER_INFO("Parallax: Finalizo creación de sprites");

	bgScrollingOffsetX1 = 0;
	bgScrollingOffsetY1 = 0;
	bgScrollingOffsetX2 = 0;
	bgScrollingOffsetY2 = 0;

	playerPosX = 0;
	playerPosY = 0;
	playerAtBorder = false;
}

void Parallax::render() {

	//PARALLAX SIGUIENDO A LA CÁMARA (SÓLO CUANDO SCROLLEA EN EL BORDE)
	if (playerAtBorder) {
		LOGGER_DEBUG("Parallax: Calculo scrolling offset");
		if (level == LEVEL1 || level == LEVEL3) {
			bgScrollingOffsetX2 -= 4;
			bgScrollingOffsetX1 -= 8;
		}
		else {
			bgScrollingOffsetY2 += 4;
			bgScrollingOffsetY1 += 8;
		}
	}

	//Chequeo que el offset esté siempre entre los límites de 0 y screenWidth
	if (level == LEVEL1 || level == LEVEL3) {
		LOGGER_DEBUG("Parallax: Verifico que los offsets esté dentro de los límites de la pantalla");
		if( bgScrollingOffsetX2 < -screenWidth) {
			bgScrollingOffsetX2 += screenWidth;
		}
		if( bgScrollingOffsetX1 < -screenWidth) {
			bgScrollingOffsetX1 += screenWidth;
		}
	}
	else {
		if( bgScrollingOffsetY2 > screenHeight) {
			bgScrollingOffsetY2 -= screenHeight;
		}
		if( bgScrollingOffsetY1 > screenHeight) {
			bgScrollingOffsetY1 -= screenHeight;
		}
	}

	//Renderizo dos iteraciones de los fondos
	//FONDO 2
	screenPosX = bgScrollingOffsetX2;
	screenPosY = bgScrollingOffsetY2;
	LOGGER_DEBUG("Parallax: Renderizo primera iteración de FONDO 2");
	bgSprite2->render(screenPosX, screenPosY);
	if (level == LEVEL1 || level == LEVEL3) {
		screenPosX += screenWidth;
	}
	else {
		screenPosY -= screenHeight;
	}
	LOGGER_DEBUG("Parallax: Renderizo segunda iteración de FONDO 2");
	bgSprite2->render(screenPosX, screenPosY);

	//FONDO 1
	screenPosX = bgScrollingOffsetX1;
	screenPosY = bgScrollingOffsetY1;
	LOGGER_DEBUG("Parallax: Renderizo primera iteración de FONDO 1");
	bgSprite1->render(screenPosX, screenPosY);
	if (level == LEVEL1 || level == LEVEL3) {
		screenPosX += screenWidth;
	}
	else {
		screenPosY -= screenHeight;
	}
	LOGGER_DEBUG("Parallax: Renderizo segunda iteración de FONDO 1");
	bgSprite1->render(screenPosX, screenPosY);


	//PARALLAX SIGUIENDO AL PERSONAJE
	/*

	const float velocidadBG1 = 1.25;
	const float velocidadBG2 = 1;

	if (level == LEVEL1 || level == LEVEL3) {
		//Calculo scrolling offset para cada fondo basado en la posición del jugador
		if (playerPosX > screenWidth) {
			int qWindow = playerPosX / screenWidth;
			bgScrollingOffsetX1 = -(playerPosX - (screenWidth * qWindow)) * velocidadBG1;
			bgScrollingOffsetX2 = -(playerPosX - (screenWidth * qWindow)) * velocidadBG2;
		}
		else {
			bgScrollingOffsetX2 = -playerPosX * velocidadBG2;
			bgScrollingOffsetX1 = -playerPosX * velocidadBG1;
		}
		bgScrollingOffsetY2 = -playerPosY * 0.1;
		bgScrollingOffsetY1 = -playerPosY * 0.2;

		//Chequeo que el offset esté siempre entre los límites de 0 y screenWidth
		if( bgScrollingOffsetX2 < -screenWidth * velocidadBG2) {
			bgScrollingOffsetX2 += screenWidth;
		}
		if( bgScrollingOffsetX1 < -screenWidth * velocidadBG1) {
			bgScrollingOffsetX1 += screenWidth * velocidadBG2;
		}
	}
	else {
		if (playerPosY > screenHeight) {
			int qWindow = playerPosY / screenHeight;
			bgScrollingOffsetY1 = -(playerPosY - (screenHeight * qWindow)) * velocidadBG1;
			bgScrollingOffsetY2 = -(playerPosY - (screenHeight * qWindow)) * velocidadBG2;
		}
		else {
			bgScrollingOffsetY2 = -playerPosY * velocidadBG2;
			bgScrollingOffsetY1 = -playerPosY * velocidadBG1;
		}
		bgScrollingOffsetY2 = -playerPosX * 0.1;
		bgScrollingOffsetY1 = -playerPosX * 0.1;

		//Chequeo que el offset esté siempre entre los límites de 0 y screenHeight
		if( bgScrollingOffsetY2 < -screenHeight) {
			bgScrollingOffsetY2 += screenHeight;
		}
		if( bgScrollingOffsetY1 < -screenHeight) {
			bgScrollingOffsetY1 += screenHeight;
		}
	}

	//Renderizo dos iteraciones de los fondos
	//FONDO 2
    screenPosX = bgScrollingOffsetX2;
    screenPosY = bgScrollingOffsetY2;
	bgSprite2->render(screenPosX, screenPosY);
	if (level == LEVEL1 || level == LEVEL3) {
		screenPosX += screenWidth * velocidadBG2;
	}
	else {
		screenPosY += screenHeight * velocidadBG2;
	}
    bgSprite2->render(screenPosX, screenPosY);

	//FONDO 1
    screenPosX = bgScrollingOffsetX1;
    screenPosY = bgScrollingOffsetY1;
    bgSprite1->render(screenPosX, screenPosY);
	if (level == LEVEL1 || level == LEVEL3) {
		screenPosX += screenWidth * velocidadBG1;
	}
	else {
		screenPosY += screenHeight * velocidadBG1;
	}
    bgSprite1->render(screenPosX, screenPosY);

    */
}

void Parallax::updatePlayerPos(int _playerPosX, int _playerPosY, bool _playerAtBorder) {
	LOGGER_DEBUG("Parallax: Actualizo posición del jugador y verifico si está en el margen para Parallax");
	playerPosX = _playerPosX;
	playerPosY = _playerPosY;
	playerAtBorder = _playerAtBorder;
}

Parallax::~Parallax() {
	LOGGER_INFO("Parallax: Inicio destrucción de sprites");
	bgSprite1->destroy();
	bgSprite2->destroy();
	LOGGER_INFO("Parallax: Finalizó destrucción de sprites");
}
