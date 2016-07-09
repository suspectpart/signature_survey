#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dir.h"
#include "options.h"

void listdir(const char *name, int level, survey survey)
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

			listdir(path, level + 1, survey);
		}
		else {
			char *dot = strrchr(entry->d_name, '.');
			if (dot && !strcmp(dot, options->extension)) {
				char* fullPath = malloc(strlen(name) + strlen(entry->d_name) + 2);
				strcpy(fullPath, name);
				strcat(fullPath, "/");
				strcat(fullPath, entry->d_name);
				survey(fullPath);
			}		
		}
    } while (entry = readdir(dir));

    closedir(dir);
}
