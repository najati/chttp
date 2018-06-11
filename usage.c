#include <stdlib.h>

#include "usage.h"
#include "die_with_error.h"

Parameters check_usage(int argc, char* argv[]) {
  Parameters parameters;

  if (argc != 3) {
    die_with_error("Usage: <bin> <port> <path>");
  }

  parameters.port = atoi(argv[1]);
  parameters.file_directory = argv[2];
  return parameters;  
}
