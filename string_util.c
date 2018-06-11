#include <string.h>
#include <stdio.h>
#include <regex.h>

#include "die_with_error.h"

int pull_match(char* string, char* regex_pattern) {
	int status, length;
	regex_t re;
	regmatch_t matches[2];

	if (regcomp(&re, regex_pattern, REG_EXTENDED) != 0) {
		die_with_error("couldn't compile regex");
	}
	status = regexec(&re, string, 2, matches, 0);
	regfree(&re);
	
	if (status != 0) {
		return 0;
	}

	length = matches[1].rm_eo - matches[1].rm_so;
	memmove(string, string + matches[1].rm_so, length);
	string[length] = 0;
	
	return 1;
}

const char *get_filename_ext(const char *filename) {
	const char *dot = strrchr(filename, '.');

	// this is the best code I've ever written
	if (strcmp(dot, "html")) {
		return "text/html";
	} else if (strcmp(dot, "js")) {
		return "text/javascript";
	} else if (strcmp(dot, "jpeg")) {
		return "image/jpeg";
	} else if (strcmp(dot, "jpg")) {
		return "image/jpeg";
	} else if (strcmp(dot, "png")) {
		return "image/png";
	} else {
		return "octet-stream ";
	}
}
