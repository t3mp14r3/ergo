#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/lists.h"
#include "../utils/input.h"
#include "../utils/serial.h"
#include "../visual/visual.h"

void rename_task(char * list_name, char * old_name) {
	printf(BOLD "\n\n    Edit task:\n\n" RESET);
	printf(DIM "    %s\n\n" RESET, old_name);
	CURSOR_SHOW();

	char * new_name;
	int new_name_len;

	new_name = input("    New task name: ", 255);
	new_name_len = strlen(new_name);

	CURSOR_HIDE();

	char * buff = read_list(list_name);
	
	Task * tasks;
	int tasks_counter;

	deserialise(buff, &tasks, &tasks_counter);

	for (int i = 0; i < tasks_counter; ++i) {
		if (!strcmp(tasks[i].name, old_name)) {
			strcpy(tasks[i].name, new_name);
			break;
		}
	}

	char * new_buff = serialise(&tasks, tasks_counter);

	write_list(list_name, new_buff);

	free(new_name);
	free(buff);
	free(new_buff);
	for (int i = 0; i < tasks_counter; ++i) {
		free(tasks[i].name);
	}
	free(tasks);
}
