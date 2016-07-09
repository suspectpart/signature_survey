#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "survey.h"
#include "unistd.h"
#include "options.h"

int total_statements = 0;

void print_sig_survey(const char* filename) {
	int c, lines = 0;
	FILE *file;

	size_t size = 512;
	size_t len = 0;
	
	char* buf = realloc(NULL, sizeof(char) * size); 

	file = fopen(filename, "r");

	if(file != NULL) {
		while((c = fgetc(file)) != EOF) {
			if(c == '\n') {
				lines++;
			}

			if(c == ';') {
				total_statements++;
			}

			if(c == '{' || c == '}' || c == ';') {
				buf[len++] = c;
				if(len == size) {
					buf = realloc(buf, sizeof(char) * (size+=128)); 
				}
			}		
		}
		
		fclose(file);
		
		if(lines >= options->minLines) {

			buf[len++] = '\0';	

			printf("%s ", filename);
			printf("%d ", lines);
			printf("%s\n", buf);
		}
	}
	free(buf);
}

void do_survey(const char* filename) {
	char *dot;
	dot  = strrchr(filename, '.');
	if (dot && !strcmp(dot, options->extension)) {
		print_sig_survey(filename);
	}		
}
