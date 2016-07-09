#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "survey.h"
#include "unistd.h"
#include "options.h"

int total_statements = 0;
int first = 1;

void print_to_stdout(const char* filename, int lines, const char* survey) {
	printf("%s ", filename);
	printf("%d ", lines);
	printf("%s\n", survey);
}

void print_to_html(const char* filename, int lines, const char* survey) {
	FILE* html;

	if(first) {
		html = fopen("sigs.html", "w+");
		fprintf(html, "<!DOCTYPE html>");
		fprintf(html, "<head><title>Signature Survey</title></head>");
		fprintf(html, "<h1>Signature Survey for Project X</h1><br />");
		fprintf(html, "<html>");
		first = 0;
	} else {
		html = fopen("sigs.html", "a+");
	}

	fprintf(html, "<a href='%s'>%s (%d)</a>: %s<br />", filename, filename, lines, survey);
	fclose(html);
}

void print_sig_survey(const char* filename) {
	int c, lines = 0;
	FILE *file;
	size_t size = 1024;
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
					buf = realloc(buf, sizeof(char) * (size+=1024)); 
				}
			}		
		}
		
		fclose(file);
		
		buf[len++] = '\0';	

		if(lines >= options->minLines) {
			print_to_stdout(filename, lines, buf);
			print_to_html(filename, lines, buf);
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
