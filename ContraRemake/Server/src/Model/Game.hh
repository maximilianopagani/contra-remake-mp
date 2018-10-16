/*
 * Game.h
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */
#ifndef GAME_HH_
#define GAME_HH_

#include "Level.hh"
#include "Player.hh"
#include "../Utils/GameParser.hh"
#include "../Utils/CollisionHelper.hh"

extern pthread_mutex_t server_mutex;

class Game
{
    public:

		Game(ServerHandler* _server, ServerMessageHandler* _serverMessageHandler, int _max_players,GameParser* gameParser);
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

        GameParser* gameParser;

        Player* player;
        Level* level;

        CameraLogic* cameraLogic;
        ServerMessageHandler* serverMessageHandler;

        //-----------------------------------------------
        //Servidor para enviar y recibir mensajes
        ServerHandler* server;

        std::queue<MessageServer*> game_recv_msgs_queue;
};

#endif /* SRC_GAME_HH_ */
