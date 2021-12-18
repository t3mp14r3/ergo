#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/input.h"
#include "../visual/visual.h"
#include "../utils/tasks.h"

void rename_list(char * old_name) {
	printf(BOLD "\n\n    Rename %s list:\n\n" RESET, old_name);
	CURSOR_SHOW();

	char * new_name;
	int new_name_len;

	new_name = input("    New name: ", 64);
	new_name_len = strlen(new_name);

	char * path = get_tasks_path();
	char old_path[strlen(path) + 13 + strlen(old_name)];
	char new_path[strlen(path) + 13 + new_name_len];

    sprintf(old_path, "%s/%s.json", path, old_name);
    sprintf(new_path, "%s/%s.json", path, new_name);

	CURSOR_HIDE();

	if (rename(old_path, new_path) != 0) {
		free(new_name);
		free(path);

		CURSOR_HIDE();
		printf("\n    Couldn't rename list!\n");
		printf(DIM "\n    Press any key to continue\n" RESET);
		raw_input("");

		return;
	}

	free(new_name);
	free(path);
}
