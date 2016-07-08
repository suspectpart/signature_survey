#include <stdio.h>
#include "unistd.h"
#include "dir.c"

static int l, s;

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
		
		if(count >= l) {

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
  	l = 0;
	s = 0;
	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, "l:s:")) != -1) {
		switch (c)
		{
			case 'l':
				l = atoi(optarg);
				break;
			case 's':
				s = atoi(optarg);
				break;
			case '?':
				if (optopt == 'l' || optopt == 's') {
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				}
				else if (isprint (optopt)) {
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				}
				else {
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				}
				return 1;
			default:
				abort();
		}
	}

	listdir(".", 0, do_survey);
	return 0;
}
