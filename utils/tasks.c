#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * get_tasks_path() {
	char * home = getenv("HOME");
	char * path = calloc(strlen(home)+22, sizeof(char));
	
	strcpy(path, home);
	strcat(path, "/.config/cerber/tasks");

	return path;
}
