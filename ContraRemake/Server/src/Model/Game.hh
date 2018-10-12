/*
 * Game.h
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */
#ifndef GAME_HH_
#define GAME_HH_

//#include "../Vista/GameView.hh"
#include "Level.hh"
#include "Player.hh"
//#include "../Utils/GameParser.hh"
#include "../Utils/CollisionHelper.hh"
#include "TcpListener.h"
//#include "LogicToViewTransporter.hh"

class Game
{
    public:

        Game(CTcpListener* _server);
        virtual ~Game();

        void init();
        void handleEvents();
        void update();
        void render();
        void destroy();

        void restartGame();
        void nextLevel();
        void endGame();

        bool state() { return enEjecucion; }

    private:

        bool enEjecucion;

        int currentLevel;

       // GameParser* gameParser;
        //GameView* gameView;
        Player* player;
        Level* level;
       // LogicToViewTransporter* logicToViewTransporter;
        CameraLogic* cameraLogic;

        //-----------------------------------------------
        //Servidor para enviar y recibir mensajes
        CTcpListener* server;
};

#endif /* SRC_GAME_HH_ */
