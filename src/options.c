#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include "options.h"

int parse_options(int argc, char* argv[], Options* options) {
	int c;
	opterr = 0;

	while ((c = getopt (argc, argv, "t:l:s:")) != -1) {
		switch (c)
		{
			case 't':
				options->extension = optarg;
				break;
			case 'l':
				options->minLines = atoi(optarg);
				break;
			case '?':
				if (optopt == 'l' || optopt == 't') {
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

	return options->extension == NULL ? 1 : 0;
}
