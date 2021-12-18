#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../visual/visual.h"
#include "../utils/lists.h"
#include "../utils/setup.h"
#include "../utils/input.h"
#include "modules.h"

void menu() {
	// Prepare the visual
	CURSOR_HIDE();

	// Prepare the variables
	char input;
	int selector = 0;
	int lists_counter;
	char ** lists;
	
	// Start menu loop
	while (1) {
		CLEAR();
		
		// Count and read the lists
		lists_counter = count_lists();
		lists = read_lists(lists_counter);

		// Render user input
		if (input == 113) {
			free_lists(lists, lists_counter);
			close();
		} else if (input == 106) {
			if (selector != (lists_counter - 1))
				selector++;
			else
				selector = 0;
		} else if (input == 107) {
			if (selector != 0)
				selector--;
			else
				selector = lists_counter - 1;
		} else if (input == 13) {
			open(lists[selector]);
		} else if (input == 104) {
			help_menu();
		} else if (input == 110) {
			new_list();
			strcpy(&input, "");
			continue;
		} else if (input == 100) {
			delete_list(lists[selector]);
			if (selector == (lists_counter - 1))
				selector--;
			strcpy(&input, "");
			continue;
		} else if (input == 114) {
			rename_list(lists[selector]);
			strcpy(&input, "");
			continue;
		}

		printf(BOLD "\n\n    Task Lists:\n\n" RESET);

		if (lists_counter == 0) {
			printf("    No lists\n");
		}

		// Display the menu
		for (int i = 0; i < lists_counter; ++i) {
			if (selector == i) {
				printf(BOLD "  ➤ %s\n" RESET, lists[i]);
			} else {
				printf("    %s\n", lists[i]);
			}
		}

		printf(DIM "\n    Press h for help" RESET);

		input = raw_input("");

		free_lists(lists, lists_counter);
		lists_counter = 0;
	}
}
