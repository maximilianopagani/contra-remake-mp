//============================================================================
// Name        : Cliente.cpp
// Author      : Giova
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
void *memset(void *s, int c, size_t n);
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace std;

int main() {
	cout<<"Inicio Cliente"<<endl;

	int port = 54000; //Puerto

	//Creo el Socket
	int network_socket;
	network_socket = socket(AF_INET,SOCK_STREAM,0);

	//Asigno una direccion para el socket que acabo de crear
	struct sockaddr_in server_address;
	server_address.sin_family =AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");


	int conecction_Status = connect(network_socket, (struct sockaddr *)&server_address,sizeof(server_address));

	//Chekeo si ocurrio algun error
	if(conecction_Status == -1 ){
		cout << "Ocurrio un error haciendo la coneccion"<<endl;
	}

	// Do-while loop
		char buf[4096];
		string userInput;

		do{
			cout << "> ";
			getline(cin, userInput);

			if (userInput.size() > 0)// Aseguro que el usuario escriba algo
			{
				// Envia un texto
				int sendResult = send(network_socket, userInput.c_str(), userInput.size() + 1, 0);
				if (sendResult != -1)
				{
					// Espera una respuesta
					memset(buf,0, 4096);
					int bytesReceived = recv(network_socket, buf, 4096, 0);
					if (bytesReceived > 0){
						// Respuesta por consola
						cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
					}
				}
			}

		} while (userInput.size() > 0);

	close(network_socket);

	return 0;

}
