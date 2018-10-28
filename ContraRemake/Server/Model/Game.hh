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
#include "../../Utils/GameParser.hh"
#include "../../Utils/CollisionHelper.hh"

extern pthread_mutex_t server_mutex;

class Game
{
    public:

		Game(ServerHandler* _server, ServerMessageHandler* _serverMessageHandler, int _max_players, GameParser* gameParser, int _FPS);
        virtual ~Game();

        void init();
        void runGame();
        void handleEvents();
        void processMessage(MessageServer* message);
        void update();
        void render();
        void destroy();

        int getMaxPlayers() { return max_players; }
        bool isValidPlayerId(int player_id) { return (player_id >= 0 && player_id < max_players); }

        void scrollLevel();
        void restartGame();
        void nextLevel();
        void endGame();

    private:

        bool enEjecucion;
        int FPS;

        int currentLevel;
        int changeLevelNextFrame = false;
        int changeLevelCooldown = 0;

        int max_players;

        GameParser* gameParser;

		std::vector<Player*> players;

        Level* level;

        CameraLogic* cameraLogic;
        ServerMessageHandler* serverMessageHandler;

        //-----------------------------------------------
        //Servidor para enviar y recibir mensajes
        ServerHandler* server;

        std::queue<MessageServer*> game_recv_msgs_queue;
};

#endif /* SRC_GAME_HH_ */
