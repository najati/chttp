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
		if (find_match(line, "^GET ([^ ]*) .*", line)) {
			if (strlen(line) == 1) {
				strcpy(request_path + strlen(request_path), "/index.html");
			} else {
				strcpy(request_path + strlen(request_path), line);
			}
		}
	}

	fprintf(stderr, "Got a request for: %s\n", request_path);

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
