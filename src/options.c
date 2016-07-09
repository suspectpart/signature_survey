#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include "options.h"

int parse_options(int argc, char* argv[], Options* options) {
	int c;
	opterr = 0;

	while ((c = getopt (argc, argv, "t:l:o:")) != -1) {
		switch (c)
		{
			case 't':
				options->extension = optarg;
				break;
			case 'l':
				options->minLines = atoi(optarg);
				break;
			case 'o':
				// TODO: check for valid formats
				options->format = optarg;
				break;
			case '?':
				if (optopt == 'l' || optopt == 't' || optopt == 'o') {
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

	if(options->format == NULL) {
		options->format = "text";
	}

	return options->extension == NULL ? 1 : 0;
}
