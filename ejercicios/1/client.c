#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAXRCVLEN 500
#define PORTNUM 9999

int main(int argc, char *argv[])
{
	int i = 0;
	char buffer[MAXRCVLEN + 1];
	int len, client, ret;
	struct sockaddr_in dest;

	client = socket(AF_INET, SOCK_DGRAM, 0);
	if (client < 0) {
		printf("Error: Socket()\n");
		return -1;
	}

	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	dest.sin_port = htons(PORTNUM);

	ret = connect(client, (struct sockaddr *)&dest, sizeof(struct sockaddr));
	if (ret < 0) {
		printf("Error: Connect()\n");
		return -1;
	}else{
		while(i < 5) {
			sendto(client, "hola", 5, 0, (struct sockaddr *)&dest, sizeof(dest));
			i++;
		}
	}

	/*len = recv(client, buffer, MAXRCVLEN, 0);
	if (len < 0) {
		printf("Error: Recv()\n");
		return -1;
	}

	buffer[len] = '\0';
	printf("Mensaje %s : %d bytes\n", buffer, len);*/

	close(client);
	return EXIT_SUCCESS;
}
