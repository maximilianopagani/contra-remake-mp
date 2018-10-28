/*
 * EnemyView.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#include "EnemyView.hh"

EnemyView::EnemyView(GameView* _gameView){

	gameView = _gameView;

	sprites[0] = sprites_e1;

	for(int i = 0; i < MAX_ENEMYS; i++){
		sprites[i][0] = new Sprite(gameView, "../.images/enemies/e1/enemy1Right.png", 16, 32, 44, 87);
		sprites[i][1] = new Sprite(gameView, "../.images/enemies/e1//enemy1Left.png", 16, 32, 44, 87);
	}

}

EnemyView::~EnemyView(){
	this->destroy();
}

void EnemyView::update(int enemy_id, int state){
	sprites[enemy_id][state]->update();
}

void EnemyView::render(int enemy_id, int state, int pos_x, int pos_y){
	sprites[enemy_id][state]->render(pos_x, pos_y);
}

void EnemyView::destroy(){

	for(int enemys = 0; enemys < MAX_ENEMYS; enemys++){

		for(int i = 0 ; i < MAX_ANIMATIONS ; i++){

			if (sprites[enemys][i]){
				sprites[enemys][i]->destroy();
			}
		}
	}
}
