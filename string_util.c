#include <string.h>
#include <stdio.h>
#include <regex.h>

#include "die_with_error.h"

int find_match(char* source, char* regex_pattern, char* dst) {
	int status, length;
	regex_t re;
	regmatch_t matches[2];

	if (regcomp(&re, regex_pattern, REG_EXTENDED) != 0) {
		die_with_error("couldn't compile regex");
	}
	status = regexec(&re, source, 2, matches, 0);
	regfree(&re);
	
	if (status != 0) {
		return 0;
	}

	length = matches[1].rm_eo - matches[1].rm_so;
	memmove(dst, source + matches[1].rm_so, length);
	dst[length] = 0;
	
	return 1;
}

// this is the best code I've ever written
const char *get_mimetype(const char *filename) {
	const char *extention = strrchr(filename, '.');
	extention++;

	if (!strcmp(extention, "html")) {
		return "text/html";
	} else if (!strcmp(extention, "js")) {
		return "text/javascript";
	} else if (!strcmp(extention, "jpeg")) {
		return "image/jpeg";
	} else if (!strcmp(extention, "jpg")) {
		return "image/jpeg";
	} else if (!strcmp(extention, "png")) {
		return "image/png";
	} else {
		return "application/octet-stream ";
	}
}
