
#include "Game.hh"

Game::Game(ServerHandler* _server, ServerMessageHandler* _serverMessageHandler, int _max_players, GameParser* _gameParser, int _FPS)
{
	enEjecucion = false;
	gameParser = _gameParser;
	level = NULL;
	currentLevel = 0;
	cameraLogic = new CameraLogic(0, 0, 800, 600);
	serverMessageHandler = _serverMessageHandler;
	server = _server;
	max_players = _max_players;
	FPS = _FPS;
	canScroll = true;
}

Game::~Game()
{
	this->destroy();
}

void Game::init()
{
	enEjecucion = true;
    currentLevel = LEVEL1;

    cameraLogic->setLevel(currentLevel);
    level = new Level(cameraLogic, currentLevel, serverMessageHandler, gameParser);

    for(int i = 0; i < max_players; i++)
    {
    	players.push_back(new Player(cameraLogic, serverMessageHandler, i));

    }
}

void Game::runGame()
{
	//============= MANEJO DEL FRAMERATE =============
	const int frameDelay = 1000 / FPS ;
	Uint32 timeAtIterationStart;
	int iterationTime;
	//================================================

	while(enEjecucion)
	{
		//============= MANEJO DEL FRAMERATE =============
		timeAtIterationStart = Utils::getTicks();
		//================================================

		//----------------------------------------------------------------------
		//Aca tengo que poner algo que reciba mensaje y los pushee
		this->handleEvents();

		//----------------------------------------------------------------------
		//Actualizo todo lo que vaya pasando acorde a los eventos
		this->update();

		//----------------------------------------------------------------------
		//Dibujo toda la escena
		this->render();

		//============= MANEJO DEL FRAMERATE =============
		iterationTime = Utils::getTicks() - timeAtIterationStart;

		if(frameDelay > iterationTime) // Si lo que tardó la iteracion es menor a lo que debe tardar un ciclo para mostrarse a la tasa de frames deseada
		{
			Utils::setDelay(frameDelay - iterationTime);
		}
		//================================================
	}
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
	std::cout<<"Game: handleEvents() - Procesando mensaje de player id: "<<message->getPlayerId()<<" y username: "<<message->getUsername()<<" Mensaje: "<<msg<<std::endl;

	sscanf(msg,"%i,%i,%[^,],%[^,],%[^,],%[^,];", &MSG_HEADER_1, &MSG_HEADER_2, param1, param2, param3, param4);

	switch(MSG_HEADER_1)
	{
		case INPUT:
		{
			switch(MSG_HEADER_2)
			{
				case KEYS:
				{
					int player_id = message->getPlayerId();
					//std::string username = message->getUsername();

					// IMPORTANTE SOLO PROCESAR UN MENSAJE DE TECLAS POR JUGADOR POR CICLO. SI POR CUALQUIER CAUSA, LLEGARA A DESENCOLAR MAS DE UN MENSAJE DE TECLAS PARA
					// UN MISMO PLAYER TENGO QUE PROCESAR SOLO UNO Y DESCARTAR EL RESTO

					if(this->isValidPlayerId(player_id))
					{
						if(!(players.at(player_id)->alreadyProcessedKeys()))
						{
							Uint8 player_keys[7];

							player_keys[0] = param1[0] - '0';
							player_keys[1] = param1[1] - '0';
							player_keys[2] = param1[2] - '0';
							player_keys[3] = param1[3] - '0';
							player_keys[4] = param1[4] - '0';
							player_keys[5] = param1[5] - '0';
							player_keys[6] = param1[6] - '0'; // tecla corresondiente a la N, avanzar nivel. Esto quizas se debería mandar en un mensaje dedicado desde cliente?

							players.at(player_id)->handleKeys(player_keys);
						}
					}
					break;
				}
			}
			break;
		}

		case INFO:
		{
			switch(MSG_HEADER_2)
			{
				case DISCONNECT:
				{
					int playerid = message->getPlayerId();
					std::string username = message->getUsername();
					std::cout<<"Game: Jugador desconectado ID: "<<playerid<<" y Username: "<<username<<std::endl;
					players.at(playerid)->freeze();
					break;
				}

				case RECONNECT:
				{
					int playerid = message->getPlayerId();
					serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, "set1/fondo1.png", "1"));
					serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, "set1/fondo2.png", "2"));
					serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, "set1/fondo3.png", "3"));
					// si no mando a recargar los fondos tira segmentation fault, seguramente pq quiere acceder a sprites nulos que no estan creados en playerview del cliente
					std::cout<<"Envío recarga a todo el mundo por la reconexion, medio negro"<<std::endl;
					Player* p = players.at(playerid);
					p->spawn(p->getPosX(), p->getPosY()-5);
					break;
				}
			}
			break;
		}
	}
}

void Game::restartGame()
{
    for(int i = 0; i < max_players; i++)
    {
    	players.back()->destroy();
    	players.pop_back();
    }

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
		    for(int i = 0; i < max_players; i++)
		    {
		    	players.at(i)->spawn(level->getSpawnPointX(), level->getSpawnPointY());
		    }
			break;

		case LEVEL2:
			level->destroy(); // y con el se borrarian enemigos, plataformas, etc. Analizar si dejarlos en memoria y solo borrarlo al salir, por si quiere rejugar
			currentLevel = LEVEL3;
			level = new Level(cameraLogic, LEVEL3,serverMessageHandler,gameParser);
		    for(int i = 0; i < max_players; i++)
		    {
		    	players.at(i)->spawn(level->getSpawnPointX(), level->getSpawnPointY());
		    }
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
    for(int i = 0; i < max_players; i++)
    {
    	players.at(i)->update();
    }

	//----------------------------------------------------------------------
	//Multiscroleo
    canScroll = true;

    for(int i = 0; i < max_players; i++) {
       if(players.at(i)->getPosX() <= cameraLogic->getCameraPosX() ){
    	   //18 es estado freezado
    	   if(players.at(i)->getState() != 18 ) {
    		   canScroll = false;
    	   }
       }
    }
    for(int i = 0; i < max_players; i++) {
    	if(canScroll) level->moveForward(players.at(i)->getPosX(), players.at(i)->getPosY());
        players.at(i)->IsFreezed( currentLevel == LEVEL2 );
    }

	//----------------------------------------------------------------------
	//Manejo de Colisiones con las plataformas

	list<Platform*>* platforms = level->getPlataformList();
	list<Platform*>::iterator platformsIterator;

    for(int i = 0; i < max_players; i++)
    {
		for(platformsIterator = platforms->begin(); platformsIterator != platforms->end(); ++platformsIterator)
		{
			if(CollisionHelper::stands(players.at(i), *platformsIterator) && players.at(i)->getState() != 18 )
			{
				players.at(i)->fallingDownStop();
				break;
			}
			else
			{
				if(players.at(i)->getState() != 18 ) players.at(i)->fallingDown();
			}
		}
    }
	//----------------------------------------------------------------------
	//Logica de reUbicar al personaje despues de caer
    for(int i = 0; i < max_players; i++)
    {
    	if(cameraLogic->outOfCameraLowerLimit(players.at(i)->getPosY()))
    	{
    		if(players.at(i)->getState() != 18 ) players.at(i)->spawn(cameraLogic->getCameraPosX()+150,cameraLogic->getCameraPosY()+200);
    		//level->restart();
    	}
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
    for(int i = 0; i < max_players; i++)
    {
    	players.at(i)->render();
    }

	serverMessageHandler->sendToAllClients(new MessageServer(VIEW, SHOW, 0));
}

void Game::destroy()
{
	LOGGER_DEBUG("Se comienza la destruccion del juego.");

    for(int i = 0; i < max_players; i++)
    {
    	players.back()->destroy();
    	players.pop_back();
    }

	level->destroy();

	//Le digo a todos los clientes que destruyan todo

	LOGGER_INFO("El juego se ha cerrado correctamente.");
}
