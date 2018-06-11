#include <sys/socket.h>

#include "usage.h"
#include "socket_util.h"
#include "die_with_error.h"
#include "handle_request.h"

#define MAX_PENDING 5

int main(int argc, char* argv[]) {
	int server_socket;
	Parameters parameters = check_usage(argc, argv);

	server_socket = create_server_socket(parameters.port);
	if (listen(server_socket, MAX_PENDING) < 0)  {
		die_with_error("listen() failed");
	}

	for (;;) {
		int client_socket = get_client_socket(server_socket);
		handle_request(client_socket, parameters.file_directory);
	}

	return 0;
}
