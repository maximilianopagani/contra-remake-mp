
#include "Game.hh"
#include "Platform.hh"

Game::Game(CTcpListener* _server){
	enEjecucion = false;
//	gameParser = NULL;
	//gameView = _gameView;
	level = NULL;
	player = NULL;
	currentLevel = 0;
	cameraLogic = new CameraLogic(0, 0, 800, 600);
//	logicToViewTransporter = _logicToViewTransporter;

	server = _server;
}

Game::~Game()
{
	this->destroy();
}

void Game::init()
{
	enEjecucion = true;

    // ES A MANERA DE PRUEBA INICIAL
	//GameParser* gameParser = new GameParser();
	//if (gameParser->loadConfiguration()) {
	//	loadDataParserModel(gameParser);
	//}
	//if (gameParser) {delete gameParser;}
	// FINAL DE PRUEBA INICIAL

    currentLevel = LEVEL1;

	//----------------------------------------------------------------------
	//En la creacion de level envio mensajes para LevelVIew
//    level = new Level(gameParser, cameraLogic, LEVEL1);

    //gameView->setLimitXY(level->getLevelWidth(), level->getLevelHeight());

    //----------------------------------------------------------------------
    //En la creacion de jugador no envio nada a vista
    player = new Player(cameraLogic,server);
}

void Game::handleEvents(){

	//----------------------------------------------------------------------
	//Aca recibe una lista de teclas las cuales procesa


	/*SDL_Event event;

	while(SDL_PollEvent(&event)){

		if(event.type == SDL_QUIT){
			enEjecucion = false ;
		}
		else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n){
			this->nextLevel();
		}
	}

	player->handleKeys(SDL_GetKeyboardState(NULL));*/
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
		//	level = new Level(gameParser, cameraLogic, LEVEL2);
			player->spawn(level->getSpawnPointX(), level->getSpawnPointY());
			break;

		case LEVEL2:
			level->destroy(); // y con el se borrarian enemigos, plataformas, etc. Analizar si dejarlos en memoria y solo borrarlo al salir, por si quiere rejugar
			currentLevel = LEVEL3;
		//	level = new Level(gameParser, cameraLogic, LEVEL3);
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


void Game::update(){

	//----------------------------------------------------------------------
	//La primera vez unicamente mira si cae o no el personaje
	player->update();

	//----------------------------------------------------------------------
	//Setea el nuevo border apartir de jugador
	level->moveForward(player->getPosX(), player->getPosY());

	//----------------------------------------------------------------------
	//Manejo de Colisiones con las plataformas

			/*list<Platform*>* platforms = level->getPlataformList();
			list<Platform*>::iterator platformsIterator;

			for(platformsIterator = platforms->begin(); platformsIterator != platforms->end(); ++platformsIterator){

				if(CollisionHelper::stands(player, *platformsIterator)){
					player->fallingDownStop();
					break;
				}
				else player->fallingDown();
			}*/

	//----------------------------------------------------------------------
	//Logica de reUbicar al personaje despues de caer

			/*if(cameraLogic->outOfCameraLowerLimit(player->getPosY()) ){
				player->spawn(level->getSpawnPointX(), level->getSpawnPointY());
				level->restart();
			}*/
}

void Game::render(){

	//----------------------------------------------------------------------
	//Mandar Mensaje de Clear
	server->Send2("gameview,clear,");

	//----------------------------------------------------------------------
	//Manda un mensaje para dibujar nivel primero(Por ahora no hace nada)
    level->render();

    //----------------------------------------------------------------------
    //Manda un mensaje para dibujar al jugador
    player->render();

    //----------------------------------------------------------------------
    //Manda mensaje para mostrar la escena
    server->Send2("gameview,show,");
}

void Game::destroy()
{
	LOGGER_DEBUG("Se comienza la destruccion del juego.");

	player->destroy();
	level->destroy();

	//Le digo a todos los clientes que destruyan todo
	//gameView->destroy();

	LOGGER_INFO("El juego se ha cerrado correctamente.");
}
