#include "Game.h"


Game::Game(GameView* _gameView)
{
	enEjecucion = false;
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

    currentLevel = LEVEL1;
    level = new Level(gameView, LEVEL1);

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
	switch(currentLevel)
	{
		case LEVEL1:
			level->destroy(); // y con el se borrarian enemigos, plataformas, etc. Analizar si dejarlos en memoria y solo borrarlo al salir, por si quiere rejugar
			currentLevel = LEVEL2;
			level = new Level(gameView, LEVEL2);
			player->spawn(level->getSpawnPointX(), level->getSpawnPointY());
			break;

		case LEVEL2:
			level->destroy(); // y con el se borrarian enemigos, plataformas, etc. Analizar si dejarlos en memoria y solo borrarlo al salir, por si quiere rejugar
			currentLevel = LEVEL3;
			level = new Level(gameView, LEVEL3);
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
	player->destroy();

	level->destroy();

	gameView->destroy();

	LOGGER_INFO("El juego se ha cerrado correctamente.");
}
