/*
 * TcpClient.h
 *
 *  Created on: Oct 4, 2018
 *      Author: giova
 */
/*#include <iostream>
#include <string>
#include <string.h>
void *memset(void *s, int c, size_t n);
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>*/

#include <string>
#include <string.h>
#include <iostream>
void *memset(void *s, int c, size_t n);
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "View/GameView.hh"
#include "View/PlayerView.hh"
#include "View/PlatformView.hh"
#include "View/LevelView.hh"
#include "View/EnemyView.hh"
#include "View/BulletView.hh"

#include <list>

using namespace std;

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

class TcpClient {
public:
	TcpClient(GameView* view);
	virtual ~TcpClient();
	void init();
	void conecctToServer();
	bool Send( std::string msg );
	bool recive();
	void close();
	void messageFilter(std::string msg);

private:
	struct mensaje{
			char nombre[20];
			int edad;
			float dinero;
	};
	mensaje msjrec;

	int network_socket;
	struct sockaddr_in server_address;
	int conecction_Status;

	GameView* view;
	PlatformView* plataformView;
	PlayerView* playerView;
	LevelView* levelView;
	EnemyView* enemyView;
	BulletView* bulletView;

	//Lista donde almaceno
	std::list<std::string> message;
	std::list<std::string>::iterator messageIterator;
};

#endif /* TCPCLIENT_H_ */
