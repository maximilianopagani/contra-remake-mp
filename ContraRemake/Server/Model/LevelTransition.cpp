/*
 * LevelTransition.cpp
 *
 *  Created on: 10 nov. 2018
 *      Author: nacho
 */

#include "LevelTransition.hh"

LevelTransition::LevelTransition(ServerMessageHandler* _serverMessageHandler, std::vector<Player*> _players) {

	serverMessageHandler = _serverMessageHandler;
	players = _players;
	for (unsigned int i = 0; i < players.size(); i++) {
		level1Score.push_back(i);
		level1Score[i] = 0;
		level2Score.push_back(i);
		level2Score[i] = 0;
		level3Score.push_back(i);
		level3Score[i] = 0;
		totalScore.push_back(i);
		totalScore[i] = 0;
	}
}

LevelTransition::~LevelTransition() {

	this->destroy();
}

void LevelTransition::updateScore(int currentLevel) {

	switch(currentLevel) {
		case 1: {
			for (unsigned int i = 0; i < players.size(); i++) {
				level1Score[i] = players[i]->getLevelScore();
				serverMessageHandler->sendToAllClients(new MessageServer(LEVELTRANSITION, LOAD, currentLevel, i, level1Score[i]));
				totalScore[i] = level1Score[i] + level2Score[i] + level3Score[i];
				serverMessageHandler->sendToAllClients(new MessageServer(LEVELTRANSITION, LOAD, 4, i, totalScore[i]));
			}
			break;
		}
		case 2: {
			for (unsigned int i = 0; i < players.size(); i++) {
				level2Score[i] = players[i]->getLevelScore();
				serverMessageHandler->sendToAllClients(new MessageServer(LEVELTRANSITION, LOAD, currentLevel, i, level2Score[i]));
				totalScore[i] = level1Score[i] + level2Score[i] + level3Score[i];
				serverMessageHandler->sendToAllClients(new MessageServer(LEVELTRANSITION, LOAD, 4, i, totalScore[i]));
			}
			break;
		}
		case 3: {
			for (unsigned int i = 0; i < players.size(); i++) {
				level3Score[i] = players[i]->getLevelScore();
				serverMessageHandler->sendToAllClients(new MessageServer(LEVELTRANSITION, LOAD, currentLevel, i, level3Score[i]));
				totalScore[i] = level1Score[i] + level2Score[i] + level3Score[i];
				serverMessageHandler->sendToAllClients(new MessageServer(LEVELTRANSITION, LOAD, 4, i, totalScore[i]));
			}
			break;
		}
	}
}

void LevelTransition::render() {

	serverMessageHandler->sendToAllClients(new MessageServer(LEVELTRANSITION, RENDER, 0));
}

void LevelTransition::destroy() {

	level1Score.clear();
	level2Score.clear();
	level3Score.clear();
	totalScore.clear();
	players.clear();
}
