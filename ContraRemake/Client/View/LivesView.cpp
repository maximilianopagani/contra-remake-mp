/*
 * LivesView.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: maximiliano
 */

#include "LivesView.hh"

LivesView::LivesView(GameView* _gameView)
{
	gameView = _gameView;

	for(int player_id = 0; player_id < 4; player_id++)
	{
		lives_sprites[player_id] = new Sprite(gameView, "../.images/lives/p" + std::to_string(player_id + 1) + "/live_icon.png", 12, 24, 12, 24);
		game_over_sprites[player_id] = new Sprite(gameView, "../.images/lives/p" + std::to_string(player_id + 1) + "/game_over.png", 66, 24, 66, 24);
	}
}

LivesView::~LivesView()
{
	this->destroy();
}

void LivesView::render(int player_id, int amount)
{
	if(amount > 0)
	{
		for(int i = 0; i < amount; i++)
		{
			lives_sprites[player_id]->render(sprites_pos_x[player_id] +  i * 17, sprites_pos_y);
		}
	}
	else
	{
		game_over_sprites[player_id]->render(sprites_pos_x[player_id], sprites_pos_y);
	}
}

void LivesView::destroy()
{
	for(int player_id = 0; player_id < 4; player_id++)
	{
		lives_sprites[player_id]->destroy();
		lives_sprites[player_id] = NULL;

		game_over_sprites[player_id]->destroy();
		game_over_sprites[player_id] = NULL;
	}
}

