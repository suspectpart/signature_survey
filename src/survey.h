/*
 * Opens single source file and prints survey to command line
 * containing the filename, total number of lines and the 
 * signature survey for that file.
*/
extern void print_sig_survey(const char*); 

/*
 * Callback for directory walker to pass files for survey printing.
*/
extern void do_survey(const char*);

extern int total_statements;
