#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../visual/visual.h"
#include "../utils/lists.h"
#include "../utils/serial.h"
#include "../utils/task.h"
#include "../utils/input.h"
#include "modules.h"

void open(char name[256]) {
	CLEAR();

	int selector = 0;
	char input;

	while (1) {
		CLEAR();

		char * buff = read_list(name);
		
		Task * tasks;
		int tasks_counter;

		deserialise(buff, &tasks, &tasks_counter);
		
		if (input == 113) {
			free(buff);
			for (int i = 0; i < tasks_counter; ++i)
				free(tasks[i].name);
			free(tasks);
			break;
		} else if (input == 106) {
			if (selector != (tasks_counter - 1))
				selector++;
			else
				selector = 0;
		} else if (input == 107) {
			if (selector != 0)
				selector--;
			else
				selector = tasks_counter - 1;
		} else if (input == 32) {
			check(name, tasks[selector].name);
			strcpy(&input, "");
			continue;
		} else if (input == 104) {
			help_open();
		} else if (input == 110) {
			new_task(name);
			strcpy(&input, "");
			continue;
		} else if (input == 13) {
			check(name, tasks[selector].name);
			strcpy(&input, "");
			continue;
		} else if (input == 114) {
			rename_task(name, tasks[selector].name);
			strcpy(&input, "");
			continue;
		} else if (input == 100) {
			delete_task(name, tasks[selector].name);
			strcpy(&input, "");
			continue;
		}

		printf(BOLD "\n\n    %s:\n\n" RESET, name);

		if (tasks_counter == 0) {
			printf("    No tasks\n");
		}

		for (int i = 0; i < tasks_counter; ++i) {
			if (selector == i) {
				printf(BOLD "  ➤ ");
			} else {
				printf("    ");
			}
			
			if (tasks[i].check == 0) {
				printf("%s\n", tasks[i].name);
			} else {
				FG_256(121);
				printf(STRIKE DIM "%s\n", tasks[i].name);
			}
			RESETF();
		}
		
		free(buff);
		for (int i = 0; i < tasks_counter; ++i) {
			free(tasks[i].name);
		}
		free(tasks);
		
		printf(DIM "\n    Press h for help" RESET);

		OUTPUT_HIDE();
		input = raw_input("");
		RESETF();
	}
}
