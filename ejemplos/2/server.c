#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORTNUM 9999

int main(int argc, char *argv[])
{
	char* msg = "<html><head><title>Prueba</title></head><body><p>Hola Miguel</p></body></html>";

	struct sockaddr_in dest;
	struct sockaddr_in serv;
	int server;
	int comp_de_error;
	socklen_t socksize = sizeof(struct sockaddr_in);

	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(PORTNUM);

	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server < 0) {
		//es un mensaje de error
		perror("Error: Socket()\n");
		return -1;
	}

	comp_de_error = bind(server, (struct sockaddr *)&serv, sizeof(struct sockaddr));
	if (comp_de_error < 0) {
		//es un mensaje de error
		perror("Error: Socket()\n");
		return -1;
	}
	listen(server, 1);

	int client = accept(server, (struct sockaddr *)&dest, &socksize);
	
	if (client < 0) {
		printf("Error: Accept()\n");
		return -1;
	}

	while(client) {
		printf("IP %s - envía un hola\n", inet_ntoa(dest.sin_addr));
		send(client, msg, strlen(msg), 0);
		//comprobar si hubo error en el envio
		close(client);
		client = accept(server, (struct sockaddr *)&dest, &socksize);
	}

	close(server);
	return EXIT_SUCCESS;
}
