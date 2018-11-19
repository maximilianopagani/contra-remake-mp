/*
 * Game.h
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */
#ifndef GAME_HH_
#define GAME_HH_

#include "Level.hh"
#include "LevelTransition.hh"
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
        void handleGameFPS();
        void handleLevelChange();
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
        bool loadTransition;

        //========== Manejo de la velocidad del juego =============
        int game_FPS, frame_max_ms_duration;
        int frame_ms_duration = 0;
        Uint32 time_at_frame_start = 0;
        //=========================================================

        int currentLevel;

        //============= Manejo del cambio de nivel ================
        bool changeLevelNextFrame = false;
        Uint32 changeLevelTime = 0; // Tiempo en ticks cuando se hizo el ultimo cambio de nivel
        static const Uint32 changeLevelCooldown = 1000;  // En milisegundos, cuanto espero hasta que pueda procesar nuevamente tecla de cambio de nive,
        //=========================================================

        int max_players;
        bool oneTime ;

        GameParser* gameParser;

		std::vector<Player*> players;

        Level* level;
        LevelTransition* levelTransition;

        CameraLogic* cameraLogic;
        ServerMessageHandler* serverMessageHandler;

        //-----------------------------------------------
        //Servidor para enviar y recibir mensajes
        ServerHandler* server;

        std::queue<MessageServer*> game_recv_msgs_queue;
};

#endif /* SRC_GAME_HH_ */
