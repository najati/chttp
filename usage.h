#pragma once

typedef struct {
  unsigned int port;
  char *file_directory;
} Parameters;

Parameters check_usage(int argc, char* argv[]);
