#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*print_survey)(const char* filename);

void listdir(const char *name, int level, print_survey prints)
{
	DIR *dir;
	struct dirent *entry;

    	if (!(dir = opendir(name))) {
		return;
	}

	if (!(entry = readdir(dir))) {
		return;
	}

    	do {
		if (entry->d_type == DT_DIR) {
			char path[1024];
			int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
			path[len] = 0;
            		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
				continue;
			}

			listdir(path, level + 1, prints);
        	}
		else {
			//printf("%*s- %s\n", level*2, "", entry->d_name);
			if(strcmp(name, ".") == 0) {
				prints(entry->d_name);
			} else {
				char* fullPath = malloc(strlen(name) + strlen(entry->d_name) + 2);
				strcpy(fullPath, name);
				strcat(fullPath, "/");
				strcat(fullPath, entry->d_name);
				prints(fullPath);
			}
		}
    } while (entry = readdir(dir));

    closedir(dir);
}
