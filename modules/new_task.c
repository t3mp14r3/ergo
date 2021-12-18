#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../utils/lists.h"
#include "../utils/input.h"
#include "../utils/serial.h"
#include "../visual/visual.h"

void new_task(char * list_name) {
	printf(BOLD "\n\n    New task:\n\n" RESET);
	CURSOR_SHOW();

	char * new_task_name;
	int new_task_name_len;

	new_task_name = input("    Task name: ", 255);
	new_task_name_len = strlen(new_task_name);

	CURSOR_HIDE();
	
	if (new_task_name_len == 0) {
		free(new_task_name);

		printf("\n    No new task name provided!\n");
		printf(DIM "\n    Press any key to continue\n" RESET);
		raw_input("");

		return;
	}

	char * buff = read_list(list_name);
	
	Task * tasks;
	int tasks_counter;

	deserialise(buff, &tasks, &tasks_counter);

	for (int i = 0; i < tasks_counter; ++i) {
		if (!strcmp(tasks[i].name, new_task_name)) {
			free(new_task_name);
			for (int i = 0; i < tasks_counter; ++i) {
				free(tasks[i].name);
			}
			free(tasks);
			free(buff);

			CURSOR_HIDE();
			printf("\n    Task with name already exists!\n");
			printf(DIM "\n    Press any key to continue\n" RESET);
			raw_input("");

			return;
		}
	}

	Task * new_tasks = realloc(tasks, sizeof(Task)*(tasks_counter+1));
	tasks = new_tasks;

	tasks[tasks_counter].name = calloc(new_task_name_len+1, sizeof(char));

	strcpy(tasks[tasks_counter].name, new_task_name);
	tasks[tasks_counter].check = false;
	
	tasks_counter++;

	char * new_buff;

	new_buff = serialise(&tasks, tasks_counter);

	write_list(list_name, new_buff);

	free(new_task_name);
	free(buff);
	for (int i = 0; i < tasks_counter; ++i) {
		free(tasks[i].name);
	}
	free(tasks);
	free(new_buff);
}
