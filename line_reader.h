
#pragma once

#define RECEIVE_BUFFER_SIZE 4096

typedef struct {
	int socket;
	char buffer[RECEIVE_BUFFER_SIZE];
	int content_size;
} LineReader;

void init_reader(LineReader* reader, int socket);
int read_line(LineReader* reader, char* line);
