/*
 * ItemView.hh
 *
 *  Created on: Nov 6, 2018
 *      Author: gmc
 */

#ifndef CLIENT_VIEW_ITEMVIEW_HH_
#define CLIENT_VIEW_ITEMVIEW_HH_

#include "GameView.hh"
#include "Sprite.hh"

class ItemView {

	enum ItemType {
		TYPE_FIREBALLFALCON,
		TYPE_FIREFIELDFALCON,
		TYPE_LASERFALCON,
		TYPE_MACHINEGUNFALCON,
		TYPE_RAPIDFIREFALCON,
		TYPE_SPREADGUNFALCON,
		TYPE_ERROR
	};

public:
	ItemView(GameView* _gameView);
	virtual ~ItemView();

	void render(int posX, int posY, int tileAmount, int typeCode);
	void destroy();

private:

	GameView* gameView;
	Sprite* sprites[7];
};

#endif /* CLIENT_VIEW_ITEMVIEW_HH_ */
