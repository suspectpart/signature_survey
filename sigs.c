#include <stdio.h>
#include "unistd.h"
#include "dir.c"

static int l, s;
static int total_statements;
char* statement;
char* extension;

void usage() {
	printf("Usage: sigs -t <extension>\n");
	printf("\t -l <n> - Only display files with at least n lines\n");
	printf("Example: sigs -t .java -l 100\n");
	printf("(Only show .java files with at least 100 lines)\n");
}

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
		
		if(lines >= l) {

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
	if (dot && !strcmp(dot, extension)) {
		print_sig_survey(filename);
	}		
}


int main(int argc, char* argv[]) {
  	l = 0;
	s = 0;
	total_statements = 0;
	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, "t:l:s:")) != -1) {
		switch (c)
		{
			case 't':
				extension = optarg;
				break;
			case 'l':
				l = atoi(optarg);
				break;
			case 's':
				s = atoi(optarg);
				break;
			case '?':
				if (optopt == 'l' || optopt == 's' || optopt == 't') {
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
	
	if(extension == NULL) {
		usage()	;
		return 1;
	}
	

	listdir(".", 0, do_survey);
	printf("Total statements: %d\n", total_statements);
	return 0;
}

