#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "line_reader.h"

#include "die_with_error.h"

void init_reader(LineReader* reader, int socket) {
	reader->socket = socket;
	memset(&reader->buffer, 0, sizeof(RECEIVE_BUFFER_SIZE));
	reader->buffer_size = 0;
}

int read_line(LineReader* reader, char* line) {
	char *newline_location;
	int newline_index;
	int chunk_size;

	if ((newline_location = strchr(reader->buffer, '\n')) == 0) {
		char* dest = reader->buffer + reader->buffer_size;
		int dest_capacity = RECEIVE_BUFFER_SIZE - reader->buffer_size;
		if ((chunk_size = recv(reader->socket, dest, dest_capacity, 0)) < 0) {
			die_with_error("recv() failed");
		}

		reader->buffer_size += chunk_size;

		if ((newline_location = strchr(reader->buffer, '\n')) == 0) {
			die_with_error("couldn't find newline");
		}
	}

	newline_index = newline_location - reader->buffer;

	memcpy(line, reader->buffer, newline_index);
	reader->buffer_size -= newline_index;
	memmove(reader->buffer, reader->buffer + newline_index + 1, reader->buffer_size);

	return newline_index-1;
}
