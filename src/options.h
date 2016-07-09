typedef struct options {
	int minLines;
	char* extension;
} Options;

extern int parse_options(int argc, char* argv[], Options*);
Options* options;
