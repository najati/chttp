#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "die_with_error.h"

void send_string(int socket, const char* string) {
	int length = strlen(string);

	if (send(socket, string, length, 0) != length) {
		die_with_error("send() failed");
	}
}

void send_file(int socket, const char* filename) {
	int count;
	char buffer[256];

	FILE *file = fopen(filename,"rb");
	if (!file) {
		die_with_error("Unable to open file!");
	}

	while ((count = fread(buffer, 1, 256, file)) > 0) {
		if (send(socket, buffer, count, 0) != count) {
			die_with_error("send() failed");
		}

		if (feof(file)) {
			break;
		}
	}

	fclose(file);
}

int create_server_socket(unsigned short port) {
  int server_socket;
  struct sockaddr_in server_address;

  if ((server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    die_with_error("socket() failed");
  }

  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(port);  

  if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
    die_with_error("bind() failed");
  }

  return server_socket; 
}

int get_client_socket(int server_socket) {
  struct sockaddr_in client_address;
  unsigned int client_address_length = sizeof(client_address);
  int client_socket;

  if ((client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_address_length)) < 0) {
    die_with_error("accept() failed");
  }
  return client_socket;
}
