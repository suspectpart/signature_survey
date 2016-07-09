#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include "options.h"
#include "sigs.h"
#include "survey.h"
#include "dir.h"

int main(int argc, char* argv[]) {
	options = (Options*) malloc(sizeof(Options));

	int parseError = parse_options(argc, argv, options);
	
	if(parseError) {
		usage();
		return 1;
	}

	listdir(".", 0, print_sig_survey);
	printf("Total statements: %d\n", total_statements);
	
	free(options);
	
	return 0;
}

void usage() {
	printf("Usage: sigs -t <extension>\n");
	printf("\t -l <n> - Only display files with at least n lines\n");
	printf("Example: sigs -t .java -l 100\n");
	printf("(Only show .java files with at least 100 lines)\n");
}
