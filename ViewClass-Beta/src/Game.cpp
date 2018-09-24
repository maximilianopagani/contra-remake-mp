
#include "Game.hh"
#include "Platform.hh"

Game::Game(GameParser* _gameParser, GameView* _gameView)
{
	enEjecucion = false;
	gameParser = _gameParser;
	gameView = _gameView;
	level = NULL;
	player = NULL;
	currentLevel = 0;
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
    level = new Level(gameParser, gameView, LEVEL1);

    //gameView->setLimitXY(level->getLevelWidth(), level->getLevelHeight());

    player = new Player(gameView);
}

void Game::handleEvents()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			enEjecucion = false ;
		}
		else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
		{
			this->nextLevel();
		}
	}

	player->handleKeys(SDL_GetKeyboardState(NULL));
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
			level = new Level(gameParser, gameView, LEVEL2);
			player->spawn(level->getSpawnPointX(), level->getSpawnPointY());
			break;

		case LEVEL2:
			level->destroy(); // y con el se borrarian enemigos, plataformas, etc. Analizar si dejarlos en memoria y solo borrarlo al salir, por si quiere rejugar
			currentLevel = LEVEL3;
			level = new Level(gameParser, gameView, LEVEL3);
			player->spawn(level->getSpawnPointX(), level->getSpawnPointY());
			break;

		case LEVEL3: // NO borrar el nivel 3, porque el ciclo sigue, y quedan varias cosas que tiene que ejecutar todavia con el puntero a Level
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
	player->update();

	level->moveForward(player->getPosX(), player->getPosY());

	//colision jugador y plataforma
	list<Platform*>* platforms = level->getPlataformList();
	list<Platform*>::iterator platformsIterator;
	for(platformsIterator = platforms->begin(); platformsIterator != platforms->end(); ++platformsIterator){
		if( CollisionHelper::stands(player, *platformsIterator) ){
			player->fallingDownStop();
			break;
		}
		else {
			player->fallingDown();
		}
	}

	//resetea la posicion de all despues de caer
	int maxPosY;
	if (currentLevel == LEVEL2) {
		maxPosY = 4000;
	}
	else {
		maxPosY = 600;
	}
	if(player->getPosY() > maxPosY) {
		player->resetPos();
		level->destroy();
		switch(currentLevel) {
			case LEVEL1:
				level = new Level(gameParser, gameView, LEVEL1);
				break;
			case LEVEL2:
				level = new Level(gameParser, gameView, LEVEL2);
				break;
			case LEVEL3:
				level = new Level(gameParser, gameView, LEVEL3);
				break;
		}

	}
}

void Game::render()
{
	gameView->clear();

    level->render();

    player->render();

    gameView->show();
}

void Game::destroy()
{
	LOGGER_DEBUG("Se comienza la destruccion del juego.");
	player->destroy();
	level->destroy();
	gameView->destroy();

	LOGGER_INFO("El juego se ha cerrado correctamente.");
}
