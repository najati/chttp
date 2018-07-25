#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <regex.h>

#include "line_reader.h"

#include "die_with_error.h"
#include "socket_util.h"
#include "string_util.h"

void get_request_path(int socket, char* request_path) {
	LineReader reader;
	init_reader(&reader, socket);

	int line_length;
	char line[RECEIVE_BUFFER_SIZE];

	while ((line_length = read_line(&reader, line)) > 0) {
		line[line_length] = 0;
		if (find_match(line, "^GET ([^ ]*) .*", line)) {
			if (strlen(line) == 1) {
				strcpy(request_path, "/index.html");
			} else {
				strcpy(request_path, line);
			}
		}
	}
}

void handle_request(int socket, char *dir) {
	char request_path[2048];
	strcpy(request_path, dir);

	get_request_path(socket, request_path + strlen(request_path));

	printf("Got a request for: %s\n", request_path);

	if (access(request_path, F_OK) != -1) {
		send_string(socket, "HTTP/1.1 200 OK\nServer: Najati\nContent-Type: ");
		send_string(socket, get_mimetype(request_path));
		send_string(socket, "\n\n");
		send_file(socket, request_path);		
	} else {
		send_string(socket, "HTTP/1.1 404 Not Found\nServer: Najati\n\nsNot Found\n");
	}

	close(socket);
}
