/*
 * LevelTransition.hh
 *
 *  Created on: 10 nov. 2018
 *      Author: nacho
 */

#ifndef SERVER_MODEL_LEVELTRANSITION_HH_
#define SERVER_MODEL_LEVELTRANSITION_HH_

#include "ServerMessageHandler.hh"
#include "Player.hh"

class LevelTransition {

public:

	LevelTransition(ServerMessageHandler* _serverMessageHandler, std::vector<Player*> players);
	virtual ~LevelTransition();

	void updateScore(int currentLevel);
	void render();
	void destroy();

private:

	ServerMessageHandler* serverMessageHandler;
	std::vector<Player*> players;
	std::vector<int> level1Score;
	std::vector<int> level2Score;
	std::vector<int> level3Score;
	std::vector<int> totalScore;
};

#endif /* SERVER_MODEL_LEVELTRANSITION_HH_ */
