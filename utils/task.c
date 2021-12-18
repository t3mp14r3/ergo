#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../utils/lists.h"
#include "../utils/serial.h"
#include "../visual/visual.h"

void check(char * list_name, char * task_name) {
	char * buff = read_list(list_name);
	
	Task * tasks;
	int tasks_counter;

	deserialise(buff, &tasks, &tasks_counter);

	for (int i = 0; i < tasks_counter; ++i) {
		if (!strcmp(tasks[i].name, task_name)) {
			if (tasks[i].check) {
				tasks[i].check = false;
			} else {
				tasks[i].check = true;
			}
			break;
		}
	}

	char * new_buff = serialise(&tasks, tasks_counter);

	write_list(list_name, new_buff);

	free(buff);
	free(new_buff);
	for (int i = 0; i < tasks_counter; ++i) {
		free(tasks[i].name);
	}
	free(tasks);
}

void delete_task(char * list_name, char * task_name) {
	char * buff = read_list(list_name);
	
	Task * tasks;
	Task * new_tasks;
	int tasks_counter;
	int add_counter = 0;

	deserialise(buff, &tasks, &tasks_counter);

	new_tasks = calloc(tasks_counter-1, sizeof(Task));

	for (int i = 0; i < tasks_counter; ++i) {
		if (strcmp(tasks[i].name, task_name)) {
			new_tasks[add_counter].name = calloc(strlen(tasks[i].name)+1, sizeof(char));
			strcpy(new_tasks[add_counter].name, tasks[i].name);
			new_tasks[add_counter].check = tasks[i].check;
			add_counter++;
		}
	}
	
	char * new_buff;

	new_buff = serialise(&new_tasks, tasks_counter-1);

	write_list(list_name, new_buff);

	free(buff);
	free(new_buff);
	for (int i = 0; i < tasks_counter; ++i) {
		free(tasks[i].name);
	}
	free(tasks);
	for (int i = 0; i < tasks_counter-1; ++i) {
		free(new_tasks[i].name);
	}
	free(new_tasks);
}
