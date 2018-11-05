
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

    for(int i = 0; i < max_players; i++)
    {
    	players.push_back(new Player(cameraLogic, serverMessageHandler, i));
    	players.at(i)->spawn(level->getSpawnPointX(), level->getSpawnPointY());

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

		if(changeLevelNextFrame)
		{
			this->nextLevel();
			changeLevelNextFrame = false;
		}

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
		//std::cout<<"Tiempo de iteracion: "<<iterationTime<<"ms"<<std::endl;

		if(frameDelay > iterationTime) // Si lo que tardó la iteracion es menor a lo que debe tardar un ciclo para mostrarse a la tasa de frames deseada
		{
			Utils::setDelay(frameDelay - iterationTime);
		}
		//================================================
	}
}

void Game::handleEvents()
{
	server->storeReceivedMsgsInExternalQueue(&game_recv_msgs_queue); // Traspaso los mensajes desde la cola compartida entre Server y Game, a la cola exclusiva de game.

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

	LOGGER_DEBUG("Game: handleEvents() - Procesando mensaje de player id: " + std::to_string(message->getPlayerId()) + " y username: " + message->getUsername() + " Mensaje: " + msg );

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
							Uint8 player_keys[6];

							player_keys[0] = param1[0] - '0';
							player_keys[1] = param1[1] - '0';
							player_keys[2] = param1[2] - '0';
							player_keys[3] = param1[3] - '0';
							player_keys[4] = param1[4] - '0';
							player_keys[5] = param1[5] - '0';

							if(param1[6] - '0') // tecla corresondiente a la N, avanzar nivel. Esto quizas se debería mandar en un mensaje dedicado desde cliente?
							{
								int currentTime = Utils::getTicks();
								if(changeLevelCooldown + 1000 < currentTime) // pongo un cooldown de 1000 milisecs pq aveces es muy rapido el detectar de la tecla y pasa de a 2 niveles
								{
									changeLevelNextFrame = true;
									changeLevelCooldown = currentTime;
								}
							}

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
					LOGGER_INFO("Jugador desconectado ID: " + std::to_string(playerid) + " y Username: " + username)
					players.at(playerid)->freeze();
					break;
				}

				case RECONNECT_SUCCESS:
				{
					int playerid = message->getPlayerId();
					serverMessageHandler->sendToClientId(playerid, new MessageServer(LEVEL, LOAD, level->getBackground1Path(), "1"));
					serverMessageHandler->sendToClientId(playerid, new MessageServer(LEVEL, LOAD, level->getBackground2Path(), "2"));
					serverMessageHandler->sendToClientId(playerid, new MessageServer(LEVEL, LOAD, level->getBackground3Path(), "3"));
					// si no mando a recargar los fondos tira segmentation fault, seguramente pq quiere acceder a sprites nulos que no estan creados en playerview del cliente
					LOGGER_INFO("Envío recarga por reconexion");
					players.at(playerid)->setOnlineAgain();
					players.at(playerid)->spawn(cameraLogic->getCameraPosX() + level->getRespawnPointX(), cameraLogic->getCameraPosY() + level->getRespawnPointY());
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
			level = new Level(cameraLogic, LEVEL2, serverMessageHandler, gameParser);
		    for(int i = 0; i < max_players; i++)
		    {
		    	players.at(i)->spawn(level->getSpawnPointX(), level->getSpawnPointY());
		    }
			break;

		case LEVEL2:
			level->destroy(); // y con el se borrarian enemigos, plataformas, etc. Analizar si dejarlos en memoria y solo borrarlo al salir, por si quiere rejugar
			currentLevel = LEVEL3;
			level = new Level(cameraLogic, LEVEL3, serverMessageHandler, gameParser);
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

void Game::scrollLevel()
{
	if(cameraLogic->canMoveForward())
	{
		int border = level->getBorder();
		int scrolling = level->getScrollingType();
		int pixels_to_scroll = 0;
		int player_pos;

		switch(scrolling)
		{
			case SCROLLING_HORIZONTAL:
			{
				int max_pixels_to_scroll = 800; // Lo maximo que voy a poder scrollear, teniendo en cuenta la distancia entre el borde (izquierdo o inferior, segun
					// sea el tipo de scroll) y el jugador online más próximo a dicho borde.

				for(int i = 0; i < max_players; i++) // Aca miro para todos los jugadores, cual es el margen mas chiquito que puedo avanzar, segun la distancia a la que estan del borde izquierdo
				{
					player_pos = players.at(i)->getPosX();

					if(players.at(i)->isOnline())
					{
						if(player_pos - cameraLogic->getCameraPosX() < max_pixels_to_scroll)
						{
							max_pixels_to_scroll = player_pos - cameraLogic->getCameraPosX();
						}
					}
				}

				for(int i = 0; i < max_players; i++) // Aca miro para todos los jugadores, cual es el que avanzó mayor cantidad de pixels despues del borde
				{
					player_pos = players.at(i)->getPosX();

					if(player_pos > border)
					{
						if(player_pos - border > pixels_to_scroll && player_pos - border <= max_pixels_to_scroll)
						{
							pixels_to_scroll = player_pos - border;
						}
					}
				}

				if(max_pixels_to_scroll <= 10) // Si hay algun tipo pegado al borde, seteo que en el siguiente frame nadie se pueda mover más que el borde
				{
					for(int i = 0; i < max_players; i++)
					{
						players.at(i)->disableMovementBeyondBorder();
					}
				}
				else
				{
					for(int i = 0; i < max_players; i++)
					{
						players.at(i)->enableMovementBeyondBorder();
					}
				}

				break;
			}

			case SCROLLING_VERTICAL: // En este caso no tengo la limitacion de que si otros jugadores estan en limite inferior me impida scrollear (como si la tenía en el horizontal)
			{
				for(int i = 0; i < max_players; i++)
				{
					player_pos = players.at(i)->getPosY();

					if(player_pos < border)
					{
						if(border - player_pos > pixels_to_scroll)
						{
							pixels_to_scroll = border - player_pos;
						}
					}
				}

				break;
			}
		}

		if(pixels_to_scroll)
		{
			level->moveForward(pixels_to_scroll);
		}
	}
}

void Game::update()
{
	list<Enemy*>* enemies = level->getEnemiesList();
	list<Enemy*>::iterator enemiesIterator;

	//============================================= IA DE ENEMIGOS ===============================================

	int pid;

	for(enemiesIterator = enemies->begin(); enemiesIterator != enemies->end(); ++enemiesIterator)
	{
		if((*enemiesIterator)->isOnScreen())
		{
			if((*enemiesIterator)->hasNoTarget())
			{
				pid = rand() % max_players;

				(*enemiesIterator)->targetPlayer(pid, players.at(pid)->getPosX(), players.at(pid)->getPosY());
			}
			else
			{
				pid = (*enemiesIterator)->getTarget(); // @suppress("Method cannot be resolved")
				(*enemiesIterator)->updateTargetPos(players.at(pid)->getPosX(), players.at(pid)->getPosY());
			}
		}
	}

	//============================================================================================================

	//===================================== ACTUALIZACION DE NIVEL Y ENEMIGOS ====================================

	level->update();

	//============================================================================================================

	//============================= MANEJO DE ACTUALIZACION DE JUGADORES CONECTADOS ==============================

    for(int i = 0; i < max_players; i++)
    {
    	if(players.at(i)->isOnline())
    	{
    		players.at(i)->update();
    	}
    }

    //============================================================================================================


    //============================================ MANEJO DE SCROLLEO ============================================

    this->scrollLevel();

    //============================================================================================================


    //============================== MANEJO DE ARRASTRE DE PERSONAJES OFFLINE ====================================

    for(int i = 0; i < max_players; i++)
    {
    	if(players.at(i)->isOffline())
    	{
    	  	players.at(i)->dragOfflinePlayer();
    	}
    }

    //============================================================================================================


    //=================================== MANEJO DE COLISIONES ===================================

	list<Platform*>* platforms = level->getPlatformsList();
	list<Platform*>::iterator platformsIterator;

    list<Bullet*>* bullets;
    list<Bullet*>::iterator bulletsIterator;

    //Jugadores-Plataforma
    for(int i = 0; i < max_players; i++)
    {
    	if(players.at(i)->isOnline())
    	{
			for(platformsIterator = platforms->begin(); platformsIterator != platforms->end(); ++platformsIterator)
			{
				if(CollisionHelper::stands(players.at(i), *platformsIterator))
				{
					players.at(i)->fallingDownStop();
					break;
				}
				else
				{
					players.at(i)->fallingDown();
				}
			}
    	}
    }

    //Enemigo-Plataforma
    for(enemiesIterator = enemies->begin(); enemiesIterator != enemies->end(); ++enemiesIterator)
    {
    	  for(platformsIterator = platforms->begin(); platformsIterator != platforms->end(); ++platformsIterator)
    	  {
    	    	if(CollisionHelper::stands(*enemiesIterator, *platformsIterator))
    	    	{
    	    		(*enemiesIterator)->fallingStop();
    	    		break;
    	    	}
    	    	else
    	    	{
    	    		(*enemiesIterator)->fallingDown();
    	    	}
    	   }
    }

    //Jugador-Enemigo
    for(int i = 0; i < max_players; i++)
    {
    	if(players.at(i)->isOnline())
    	{
    		for(enemiesIterator = enemies->begin(); enemiesIterator != enemies->end(); ++enemiesIterator)
    		{
    			if(CollisionHelper::collides(players.at(i), *enemiesIterator))
    			{
    			   	players.at(i)->wasHit();
    			   	break;
    			}
    		}
    	}
    }

    //BalasEnemigo-Jugador
    for(enemiesIterator = enemies->begin(); enemiesIterator != enemies->end(); ++enemiesIterator)
	{
    	bullets = (*enemiesIterator)->getBulletList(); // @suppress("Method cannot be resolved")

    	for(bulletsIterator = bullets->begin(); bulletsIterator != bullets->end();)
		{
			bool collided = false;

			for(int i = 0; i < max_players; i++)
			{
				if(players.at(i)->isOnline())
				{
					if(CollisionHelper::collides(*bulletsIterator, players.at(i)))
				    {
						players.at(i)->wasHit();

						delete (*bulletsIterator);
						bullets->erase(bulletsIterator++); // Muevo el iterador al siguiente, y borro el valor anterior del iterador

						collided = true;

						break;
				    }
				}
			}

			if(!collided) // Si no colisionó, muevo el iterador manualmente (si colisionó ya lo moví al eliminarlo)
			{
				++bulletsIterator;
			}
		}
	}

    //BalasJugador-Enemigo
    for(int i = 0; i < max_players; i++)
    {
    	if(players.at(i)->isOnline())
    	{
        	bullets = players.at(i)->getBulletList();

        	for(bulletsIterator = bullets->begin(); bulletsIterator != bullets->end();)
        	{
        		bool collided = false;

        		for(enemiesIterator = enemies->begin(); enemiesIterator != enemies->end();)
        		{
        			if(CollisionHelper::collides(*bulletsIterator, *enemiesIterator))
        			{
        				serverMessageHandler->sendToAllClients(new MessageServer(SOUND,LOAD,2,0));
        			    //level->deleteEnemy(*enemiesIterator); // ver con cuidado esto de borrar cosas mientras se itera una lista que la contiene
        			    delete (*enemiesIterator);
        			    enemies->erase(enemiesIterator++); // Muevo el iterador al siguiente, y borro el valor anterior del iterador

        			    delete (*bulletsIterator);
        			    bullets->erase(bulletsIterator++); // Muevo el iterador al siguiente, y borro el valor anterior del iterador

        			    collided = true;

        			    break;
        			}
        			else // Si no colisionó, muevo el iterador manualmente (si colisionó ya lo moví al eliminarlo)
        			{
        				 ++enemiesIterator;
        			}
        		}

        		if(!collided) // Si no colisionó, muevo el iterador manualmente (si colisionó ya lo moví al eliminarlo)
        		{
        			++bulletsIterator;
        		}
        	}
    	}
    }

    //============================================================================================================

    //============================================= MANEJO DE CAIDAS =============================================

    for(int i = 0; i < max_players; i++)
    {
    	if(players.at(i)->isOnline()) // si yo no pongo esto, tambien va a spawnear a los offline y les cambia el estado y el sprite.
    	{
			if(cameraLogic->outOfCameraLowerLimit(players.at(i)->getPosY() + 50))
			{
				players.at(i)->spawn(cameraLogic->getCameraPosX() + level->getRespawnPointX(), cameraLogic->getCameraPosY() + level->getRespawnPointY());
				serverMessageHandler->sendToAllClients(new MessageServer(SOUND,LOAD,3,0));
			}
    	}
    }

    //============================================================================================================
}

void Game::render()
{
	serverMessageHandler->sendToAllClients(new MessageServer(VIEW, CLEAR, 0));

    level->render();

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
