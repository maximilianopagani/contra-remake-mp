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
#include "../../Utils/ItemTypes.hh"

class ItemView
{
	public:

		ItemView(GameView* _gameView);
		virtual ~ItemView();

		void render(int posX, int posY, int type);
		void destroy();

	private:

		GameView* gameView;
		Sprite* sprites[MAX_ITEMS_TYPES];
};

#endif /* CLIENT_VIEW_ITEMVIEW_HH_ */
