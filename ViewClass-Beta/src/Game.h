/*
 * Game.h
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Level.h"
#include "Headers.h"

class Game
{
    public:

        Game(GameView* gameView);

        void init();
        void handleEvents();
        void update();
        void render();
        void destroy();
        bool state() { return enEjecucion; }

        virtual ~Game();

    private:

        GameView* gameView;
        bool enEjecucion;

        Player* player;
        Level* level;

};

#endif /* SRC_GAME_H_ */
