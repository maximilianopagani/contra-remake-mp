
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


using namespace std;

#define MAX_BUFFER_SIZE (49152)

// Adelanto la declaracion de la clase
class CTcpListener;

// Devolucion de la llamada de datos
typedef void(*MessageRecievedHandler)(CTcpListener* listener, int socketId, std::string msg);

class CTcpListener{

public:

	// Constructor
	CTcpListener(std::string ipAddress, int port, MessageRecievedHandler handler);

	// Destructor
	~CTcpListener();
	
	// Envia un mensaje a un cliente especifico
	void Send(int clientSocket, std::string msg);

	// Initialize
	bool Init();

	// Loop principal del programa
	void Run();

	// Clean
	void Cleanup();

private:

	// Creo un socket
	int CreateSocket();

	// Espero por una coneccion
	int WaitForConnection(int listening);

	// Direccion del servidor
	std::string	m_ipAddress;

	// Puerto del servidor(Por donde escucha)
	int	m_port;

	// Manejador del mensaje recibido
	MessageRecievedHandler	MessageReceived;
};
