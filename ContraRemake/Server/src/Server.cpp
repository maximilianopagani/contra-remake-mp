#include <iostream>
#include <string>

#include "TcpListener.h"

using namespace std;

int ServerMain(int argc, char** argv)
{
	cout<<"Server inicializado"<<endl;

	CTcpListener server("127.0.0.1", 54000);
	
	if (server.Init())
	{
		server.Run(argc,argv);
	}

	return 0;
}


