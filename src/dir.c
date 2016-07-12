#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dir.h"
#include "options.h"

typedef struct dirent* Directory;

int is_current_or_parent(const Directory directory) {
	return (
			strcmp(directory->d_name, ".")  == 0
		||  strcmp(directory->d_name, "..") == 0
	);
}

void listdir(const char *name, int level, survey survey)
{
	DIR *dir;
	Directory directory;

	if (!(dir = opendir(name))) {
		return;
	}

	if (!(directory = readdir(dir))) {
		return;
	}

	do {
		if (directory->d_type == DT_DIR) {
			char path[1024];
			int len = snprintf(path, sizeof(path)-1, "%s/%s", name, directory->d_name);
			path[len] = 0;

			if (is_current_or_parent(directory)) {
				continue;
			}

			listdir(path, level + 1, survey);
		}
		else {
			char *dot = strrchr(directory->d_name, '.');
			if (dot && !strcmp(dot, options->extension)) {
				char* fullPath = malloc(strlen(name) + strlen(directory->d_name) + 2);
				strcpy(fullPath, name);
				strcat(fullPath, "/");
				strcat(fullPath, directory->d_name);
				survey(fullPath);
			}
		}
    } while (directory = readdir(dir));

    closedir(dir);
}
