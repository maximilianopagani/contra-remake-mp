/*
 * ItemView.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: gmc
 */

#include "ItemView.hh"

ItemView::ItemView(GameView* _gameView) {
	gameView = _gameView;

	// TODO ver lo hardcodeado

	sprites[TYPE_FIREBALLFALCON] = new Sprite(gameView, "../.images/items/FireBallFalcon.png", 24, 15, 24, 15);
	sprites[TYPE_FIREFIELDFALCON] = new Sprite(gameView, "../.images/items/ForceFieldFalcon.png", 24, 15, 24, 15);
	sprites[TYPE_LASERFALCON] = new Sprite(gameView, "../.images/items/LaserFalcon.png", 24, 15, 24, 15);
	sprites[TYPE_MACHINEGUNFALCON] = new Sprite(gameView, "../.images/items/MachineGunFalcon.png", 24, 15, 24, 15);
	sprites[TYPE_RAPIDFIREFALCON] = new Sprite(gameView, "../.images/items/RapidFireFalcon.png", 24, 15, 24, 15);
	sprites[TYPE_SPREADGUNFALCON] = new Sprite(gameView, "../.images/items/SpreadGunFalcon.png", 24, 15, 24, 15);
	sprites[TYPE_ERROR] = new Sprite(gameView, "", 24, 15, 24, 15);
}

ItemView::~ItemView()
{
	this->destroy();
}

void ItemView::render(int pos_x, int pos_y, int tileAmount, int typeCode)
{
	for(int i = 0; i < tileAmount; i++)
	{
		sprites[typeCode]->render(pos_x + i * 24, pos_y);
	}
}

void ItemView::destroy()
{
	sprites[TYPE_FIREBALLFALCON]->destroy();
	sprites[TYPE_FIREFIELDFALCON]->destroy();
	sprites[TYPE_LASERFALCON]->destroy();
	sprites[TYPE_MACHINEGUNFALCON]->destroy();
	sprites[TYPE_RAPIDFIREFALCON]->destroy();
	sprites[TYPE_SPREADGUNFALCON]->destroy();
	sprites[TYPE_ERROR]->destroy();

	sprites[TYPE_FIREBALLFALCON] = NULL;
	sprites[TYPE_FIREFIELDFALCON] = NULL;
	sprites[TYPE_LASERFALCON] = NULL;
	sprites[TYPE_MACHINEGUNFALCON] = NULL;
	sprites[TYPE_RAPIDFIREFALCON] = NULL;
	sprites[TYPE_SPREADGUNFALCON] = NULL;
	sprites[TYPE_ERROR] = NULL;
}
