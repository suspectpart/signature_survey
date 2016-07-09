typedef struct options {
	int minLines;
	char* extension;
	char* format;
} Options;

extern int parse_options(int argc, char* argv[], Options*);
Options* options;
