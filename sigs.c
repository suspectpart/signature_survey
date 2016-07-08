#include <stdio.h>
#include "unistd.h"
#include "dir.c"

static int threshold;

void print_sig_survey(const char* filename) {
	int c, count = 0;
	FILE *file;

	size_t size = 512;
	size_t len = 0;
	
	char* buf;

	buf = realloc(NULL, sizeof(char) * size); 

	file = fopen(filename, "r");

	if(file != NULL) {

		while((c = fgetc(file)) != EOF) {
			if(c == '\n') {
				count++;
			}
			if(c == '{' || c == '}' || c == ';') {
				buf[len++] = c;
				if(len == size) {
					buf = realloc(buf, sizeof(char) * (size+=128)); 
				}
			}		
		}
		
		fclose(file);

		if(count >= threshold) {

			buf[len++] = '\0';	

			printf("%s ", filename);
			printf("%s", buf);
			printf(" (%d)\n", count);
		}
	}
}

void do_survey(const char* filename) {
	char *dot;
	dot  = strrchr(filename, '.');
	if (dot && !strcmp(dot, ".java")) {
		print_sig_survey(filename);
	}		
}


int main(int argc, char* argv[]) {
	threshold = 0;

	if(argc > 1) {
		sscanf (argv[1],"%d", &threshold);
	}

	listdir(".", 0, do_survey);
	return 0;
}
