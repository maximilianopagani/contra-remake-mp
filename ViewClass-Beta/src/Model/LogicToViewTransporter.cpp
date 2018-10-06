/*
 * LogicToViewTransporter.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#include "LogicToViewTransporter.hh"

LogicToViewTransporter::LogicToViewTransporter(GameView* _gameView, BulletView* _bulletView, EnemyView* _enemyView/*, PlatformView* _platformView, PlayerView* _playerView, LevelView* _levelView*/)
{
	gameView = _gameView;
	bulletView = _bulletView;
	enemyView = _enemyView;
	//platformView = _platformView;
	//playerView = _playerView;
	//levelView = _levelView;
}

LogicToViewTransporter::~LogicToViewTransporter()
{
	// TODO Auto-generated destructor stub
}

void LogicToViewTransporter::sendToDraw(TransportDestination destination, int pos_x, int pos_y)
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
			break;

		case PLAYERVIEW:
			break;

		case PLATFORMVIEW:
			break;
	}
}

void LogicToViewTransporter::sendToLoad(TransportDestination destination, string path, int x, int y, int w, int h)
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
			break;

		case PLAYERVIEW:
			break;

		case PLATFORMVIEW:
			break;
	}
}

