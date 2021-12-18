#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/lists.h"
#include "../utils/input.h"
#include "../visual/visual.h"
#include "../utils/tasks.h"

void new_list() {
	printf(BOLD "\n\n    New list:\n\n" RESET);
	CURSOR_SHOW();

	char * new_list_name;
	int new_list_name_len;
	int lists_counter;
	char ** existing_lists;

	new_list_name = input("    List name: ", 64);
	new_list_name_len = strlen(new_list_name);

	if (new_list_name_len == 0) {
		free(new_list_name);

		CURSOR_HIDE();
		printf("\n    No new list name provided!\n");
		printf(DIM "\n    Press any key to continue\n" RESET);
		raw_input("");

		return;
	}

	lists_counter = count_lists();
	existing_lists = read_lists(lists_counter);

	for (int i = 0; i < lists_counter; ++i) {
		if (!strcmp(existing_lists[i], new_list_name)) {
			free(new_list_name);
			free_lists(existing_lists, lists_counter);

			CURSOR_HIDE();
			printf("\n    List with name already exists!\n");
			printf(DIM "\n    Press any key to continue\n" RESET);
			raw_input("");

			return;
		}
	}

	char * path = get_tasks_path();
	char new_list_path[strlen(path)+13+new_list_name_len];
	sprintf(new_list_path, "%s/%s.json", path, new_list_name);

	FILE * file;

    file = fopen(new_list_path, "w");

    if (file == NULL) {
		free(new_list_name);
		free_lists(existing_lists, lists_counter);
		free(path);

		CURSOR_HIDE();
		printf("\n    Couldn't create new list file!\n");
		printf(DIM "\n    Press any key to continue\n" RESET);
		raw_input("");

		return;
    }

    fputs("{\"tasks\":[]}", file);
	
	CURSOR_HIDE();

    fclose(file);
	free(new_list_name);
	free_lists(existing_lists, lists_counter);
	free(path);
}
