
#include "Game.hh"

Game::Game(ServerHandler* _server, ServerMessageHandler* _serverMessageHandler, int _max_players,GameParser* _gameParser)
{
	enEjecucion = false;
	gameParser = _gameParser;
	level = NULL;
	player = NULL;
	currentLevel = 0;
	cameraLogic = new CameraLogic(0, 0, 800, 600);
	serverMessageHandler = _serverMessageHandler;
	server = _server;
	max_players = _max_players;
}

Game::~Game()
{
	this->destroy();
}

void Game::init()
{
	enEjecucion = true;
    currentLevel = LEVEL1;

    level = new Level(cameraLogic, currentLevel, serverMessageHandler, gameParser);
    player = new Player(cameraLogic, serverMessageHandler);
}

void Game::handleEvents()
{
	server->getNewReceivedMessages(&game_recv_msgs_queue); // Traspaso los mensajes desde la cola compartida entre Server y Game, a la cola exclusiva de game.

	MessageServer* message;

	while(!game_recv_msgs_queue.empty())
	{
		message = game_recv_msgs_queue.front();
		game_recv_msgs_queue.pop();
		this->processMessage(message); // PROCESAR EVENTOS
		delete message;
	}

	serverMessageHandler->sendToAllClients(new MessageServer(REQUEST, KEYS, 0));
}

void Game::processMessage(MessageServer* message)
{
	int MSG_HEADER_1, MSG_HEADER_2;
	char param1[32]; char param2[32]; char param3[32]; char param4[32];
	char msg[256];

	message->getContent(msg);
	std::cout<<"Game: handleEvents() - Procesando mensaje: "<<msg<<std::endl;

	sscanf(msg,"%i,%i,%[^,],%[^,],%[^,],%[^,];", &MSG_HEADER_1, &MSG_HEADER_2, param1, param2, param3, param4);

	switch(MSG_HEADER_1)
	{
		case INPUT:
		{
			switch(MSG_HEADER_2)
			{
				case KEYS:
				{
					// IMPORTANTE SOLO PROCESAR UN MENSAJE DE TECLAS POR JUGADOR POR CICLO. SI POR CUALQUIER CAUSA, LLEGARA A DESENCOLAR MAS DE UN MENSAJE DE TECLAS PARA
					// UN MISMO PLAYER TENGO QUE PROCESAR SOLO UNO Y DESCARTAR EL RESTO

					if(!player->alreadyProcessedKeys()) // cuando implementemos lista de jugadores o ids de jugadores, esto bajaría hasta el param1 y sabriamos la ID del pj que es
					{
						Uint8 player_keys[7];

						player_keys[0] = param1[0] - '0';
						player_keys[1] = param1[1] - '0';
						player_keys[2] = param1[2] - '0';
						player_keys[3] = param1[3] - '0';
						player_keys[4] = param1[4] - '0';
						player_keys[5] = param1[5] - '0';
						player_keys[6] = param1[6] - '0'; // tecla corresondiente a la N, avanzar nivel. Esto quizas se debería mandar en un mensaje dedicado desde cliente?

						player->handleKeys(player_keys);
					}

					break;
				}
			}

			break;
		}
	}
}

void Game::restartGame()
{
	player->destroy();

	level->destroy();

	this->init();

	LOGGER_INFO("El juego se ha reiniciado correctamente.");
}

void Game::nextLevel()
{
	LOGGER_INFO("Se inicia nuevo nivel : " + currentLevel);

	switch(currentLevel)
	{
		case LEVEL1:
			level->destroy(); // y con el se borrarian enemigos, plataformas, etc. Analizar si dejarlos en memoria y solo borrarlo al salir, por si quiere rejugar
			currentLevel = LEVEL2;
			level = new Level(cameraLogic, LEVEL2,serverMessageHandler,gameParser);
			player->spawn(level->getSpawnPointX(), level->getSpawnPointY());
			break;

		case LEVEL2:
			level->destroy(); // y con el se borrarian enemigos, plataformas, etc. Analizar si dejarlos en memoria y solo borrarlo al salir, por si quiere rejugar
			currentLevel = LEVEL3;
			level = new Level(cameraLogic, LEVEL3,serverMessageHandler,gameParser);
			player->spawn(level->getSpawnPointX(), level->getSpawnPointY());
			break;

		case LEVEL3: // No borrar el nivel 3, porque el ciclo sigue, y quedan varias cosas que tiene que ejecutar todavia con el puntero a Level
			endGame();
	}
}

void Game::endGame()
{
	bool want_replay = true; // Hasta que haya algun menu o nunca si no lo implementamos

	if(want_replay)
		restartGame();
	else
		enEjecucion = false;
}


void Game::update()
{
	//----------------------------------------------------------------------
	//La primera vez unicamente mira si cae o no el personaje
	player->update();

	//----------------------------------------------------------------------
	//Setea el nuevo border apartir de jugador
	level->moveForward(player->getPosX(), player->getPosY());

	//----------------------------------------------------------------------
	//Manejo de Colisiones con las plataformas

	list<Platform*>* platforms = level->getPlataformList();
	list<Platform*>::iterator platformsIterator;

	for(platformsIterator = platforms->begin(); platformsIterator != platforms->end(); ++platformsIterator){

		if(CollisionHelper::stands(player, *platformsIterator)){
			player->fallingDownStop();
			break;
		}
		else player->fallingDown();
	}

	//----------------------------------------------------------------------
	//Logica de reUbicar al personaje despues de caer

			if(cameraLogic->outOfCameraLowerLimit(player->getPosY()) ){
				player->spawn(level->getSpawnPointX(), level->getSpawnPointY());
				level->restart();
			}
}

void Game::render()
{
	serverMessageHandler->sendToAllClients(new MessageServer(VIEW, CLEAR, 0));

	//----------------------------------------------------------------------
	//Manda un mensaje para dibujar nivel primero(Por ahora no hace nada)
    level->render();

    //----------------------------------------------------------------------
    //Manda un mensaje para dibujar al jugador
    player->render();

	serverMessageHandler->sendToAllClients(new MessageServer(VIEW, SHOW, 0));
}

void Game::destroy()
{
	LOGGER_DEBUG("Se comienza la destruccion del juego.");

	player->destroy();
	level->destroy();

	//Le digo a todos los clientes que destruyan todo

	LOGGER_INFO("El juego se ha cerrado correctamente.");
}
