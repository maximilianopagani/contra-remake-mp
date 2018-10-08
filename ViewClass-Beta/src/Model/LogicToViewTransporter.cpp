/*
 * LogicToViewTransporter.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#include "LogicToViewTransporter.hh"

LogicToViewTransporter::LogicToViewTransporter(GameView* _gameView)
{
	bulletView = new BulletView(_gameView);
	enemyView = new EnemyView(_gameView);
	platformView = new PlatformView(_gameView);
	playerView = new PlayerView(_gameView);
	levelView = new LevelView(_gameView);
	gameView = _gameView;
}

LogicToViewTransporter::~LogicToViewTransporter()
{
	bulletView->destroy();
	enemyView->destroy();
	platformView->destroy();
	playerView->destroy();
	levelView->destroy();
	gameView = NULL;
}

void LogicToViewTransporter::sendToDraw(TransportDestination destination, PlayerState aState, int pos_x, int pos_y)
{
	playerView->render(aState, pos_x, pos_y);
}

void LogicToViewTransporter::sendToDraw(TransportDestination destination, int pos_x, int pos_y)
{
	sendToDraw(destination, pos_x, pos_y, 0);
}

void LogicToViewTransporter::sendToDraw(TransportDestination destination, int pos_x, int pos_y, int id)
{
	switch(destination)
	{
		case BULLETVIEW:
			bulletView->render(pos_x, pos_y);
			break;

		case ENEMYVIEW:
			enemyView->render(pos_x, pos_y);
			break;

		case GAMEVIEW:
			break;

		case LEVELVIEW:
			levelView->render(pos_x, pos_y, id);
			break;

		case PLAYERVIEW:
//			playerView->render(pos_x, pos_y);
			break;

		case PLATFORMVIEW:
			platformView->render(pos_x, pos_y, id);
			break;
	}
}

void LogicToViewTransporter::sendToLoad(TransportDestination destination, string type)
{
	sendToLoad(destination, type, 0, 0);
}

void LogicToViewTransporter::sendToLoad(TransportDestination destination, string path, int background)
{
	sendToLoad(destination, path, background, 0);
}

void LogicToViewTransporter::sendToLoad(TransportDestination destination, string path, int w, int h)
{
	switch(destination)
	{
		case BULLETVIEW:
			break;

		case ENEMYVIEW:
			enemyView->loadSprite(path, w, h);
			break;

		case GAMEVIEW:
			break;

		case LEVELVIEW:
			levelView->loadSprite(path, w);
			break;

		case PLAYERVIEW:
			playerView->update(PlayerStateHandler::stringToState(path));
			break;

		case PLATFORMVIEW:
			platformView->loadSprite(path);
			break;
	}
}

