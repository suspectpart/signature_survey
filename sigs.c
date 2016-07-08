#include <stdio.h>
#include "unistd.h"
#include "dir.c"

void print_sig_survey(const char* filename) {
	int c, count = 0;
	FILE *file;
	
	file = fopen(filename, "r");

	if(file != NULL) {
		printf("%s ", filename);

		while((c = fgetc(file)) != EOF) {
			if(c == '\n') {
				count++;
			}
			if(c == '{' || c == '}' || c == ';') {
				printf("%c", (char) c);
			}		
		}
		printf(" (%d)\n", count);

		fclose(file);
	}

}

void print_text(const char* filename) {
	char *dot;
	dot  = strrchr(filename, '.');
	if (dot && !strcmp(dot, ".java")) {
		print_sig_survey(filename);
	}		
}

int main(int argc, char* argv[]) {
	listdir(".", 0, print_text);
	return 0;
}
