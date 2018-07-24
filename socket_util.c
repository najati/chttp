#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "die_with_error.h"

#define SEND_FILE_BUFFER_SIZE 1024

struct sockaddr_in create_socket_address(port) {
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(port);

  return server_address;
}
 
int create_server_socket(unsigned short port) {
  int server_socket;

  if ((server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    die_with_error("socket() failed");
  } 

  struct sockaddr_in server_address = create_socket_address(port);
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

void send_string(int socket, const char* string) {
	int length = strlen(string);

	if (send(socket, string, length, 0) != length) {
		die_with_error("send() failed");
	}
}

void send_file(int socket, const char* filename) {
	int count;
	char buffer[SEND_FILE_BUFFER_SIZE];

	FILE *file = fopen(filename,"rb");
	if (!file) {
		die_with_error("Unable to open file!");
	}

	while ((count = fread(buffer, 1, SEND_FILE_BUFFER_SIZE, file)) > 0) {
		if (send(socket, buffer, count, 0) != count) {
			die_with_error("send() failed");
		}
	}

	fclose(file);
}
