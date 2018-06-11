#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <regex.h>

#include "line_reader.h"

#include "die_with_error.h"
#include "socket_util.h"
#include "string_util.h"

void handle_request(int socket, char *dir) {
	char request_path[1024];
	strcpy(request_path, dir);

	char line[RECEIVE_BUFFER_SIZE];
	int line_length;

	LineReader reader;
	init_reader(&reader, socket);

	while ((line_length = read_line(&reader, line)) > 0) {
		line[line_length] = 0;
		if (pull_match(line, "^GET\\s([^ \t\r\n\v\f\?]*).*")) {
			if (strlen(line) == 1) {
				strcpy(request_path + strlen(request_path), "/index.html");
			} else {
				strcpy(request_path + strlen(request_path), line);
			}
		}
	}

	fprintf(stderr, "Got a request for: %s\n", request_path);

	if (access(request_path, F_OK) != -1) {
		send_string(socket, "HTTP/1.1 200 OK\n");
		send_string(socket, "Server: Najati\n");
		send_string(socket, "Content-Type: ");
		send_string(socket, get_filename_ext(request_path));
		send_string(socket, "\n");
		send_string(socket, "\n");
		send_file(socket, request_path);		
	} else {
		send_string(socket, "HTTP/1.1 404 Not Found\n");
		send_string(socket, "Server: Najati\n");
		send_string(socket, "\n");
		send_string(socket, "Not Found\n");
	}

	close(socket);
}
