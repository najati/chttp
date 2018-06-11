#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "socket_util.h"
#include "die_with_error.h"
#include "handle_request.h"

#define MAX_PENDING 5

int main(int argc, char* argv[]) {
	int server_socket;
	unsigned short port;
	char *fileDirectory;

	if (argc != 3) { 
		printf("Usage: <bin> <port> <path>");
		exit(1);
	}

	port = atoi(argv[1]);
	fileDirectory = argv[2];

	server_socket = create_server_socket(port);
	if (listen(server_socket, MAX_PENDING) < 0)  {
		die_with_error("listen() failed");
	}

	for (;;) {
		int client_socket = get_client_socket(server_socket);
		handle_client(client_socket, fileDirectory);
	}

}