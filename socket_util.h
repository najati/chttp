
#pragma once

void send_string(int socket, const char* string);
void send_file(int socket, const char* filename);
int create_server_socket(unsigned short port);
int get_client_socket(int server_socket);