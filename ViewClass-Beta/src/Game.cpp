#include "Game.h"


Game::Game(GameView* gameView)
{
	this->gameView = gameView;
	enEjecucion = false;
	level = NULL;
	player = NULL;
}

Game::~Game(){}

void Game::init()
{
	enEjecucion = true;
    level = new Level(gameView, LEVEL1);
    player= new Player(gameView);
}

void Game::handleEvents()
{
//TODO
}

void Game::update()
{
	player->update();

	level->updateCamera(player->getPosX(), player->getPosY());

}

void Game::render()
{

	gameView->clear();

    //Render background
    level->render();

    //Copy a portion of the texture to the current rendering target.
    player->render();

    // present de SDL
    gameView->show();

}

void Game::destroy()
{
	player->destroy();

	level->destroy();

	gameView->destroy();

	std::cout<<std::endl<<"Se cerro el juego correctamente"<<std::endl;
}
