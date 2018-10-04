
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "TcpListener.h"

using namespace std;

void Listener_MessageReceived(CTcpListener* listener, int client, string msg){

	if (msg == "Hola")	listener->Send(client,"Como estas");
}


int main(){

	cout<<"Inicio Server"<<endl;

	CTcpListener server("127.0.0.1", 54000, Listener_MessageReceived);
	
	if (server.Init())
	{
		server.Run();
	}

	return 0;
}

