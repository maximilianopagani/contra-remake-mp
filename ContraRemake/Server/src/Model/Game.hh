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

class Game
{
    public:

		Game(ServerHandler* _server, ServerMessageHandler* _serverMessageHandler, int _max_players);
        virtual ~Game();

        void init();
        void handleEvents();
        void update();
        void render();
        void destroy();
        int getMaxPlayers() { return max_players; }

        void restartGame();
        void nextLevel();
        void endGame();

        bool state() { return enEjecucion; }

    private:

        bool enEjecucion;

        int currentLevel;
        int max_players;

       // GameParser* gameParser;
        //GameView* gameView;
        Player* player;
        Level* level;

        CameraLogic* cameraLogic;
        ServerMessageHandler* serverMessageHandler;

        //-----------------------------------------------
        //Servidor para enviar y recibir mensajes
        ServerHandler* server;
};

#endif /* SRC_GAME_HH_ */
