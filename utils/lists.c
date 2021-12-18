#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "dirent.h"

#include "tasks.h"

int count_lists() {
    DIR * directory;
    struct dirent * entity;
	struct stat file_info;
    int counter = 0;

    // Open directory
	char * path = get_tasks_path();

    if (directory = opendir(path)) {
		while (entity = readdir(directory)) {
			char file_path[strlen(path)+70];
			strcpy(file_path, path);
			strcat(file_path, "/");
			strcat(file_path, entity->d_name);

			lstat(file_path, &file_info);

			if (entity && (S_ISREG(file_info.st_mode))) {
				counter = counter + 1;
			}

		}
	} else {
		printf("DIRECTORY NOT FOUND!\n");
	}

	free(path);

    closedir(directory);

    return counter;
}

char ** read_lists(int lists_counter) {
    DIR * directory;
    struct dirent * entity;
    int read_counter = 0;
    char ** lists;
	struct stat file_info;

    // Allocate lists variable
    lists = (char **) calloc(lists_counter*64, sizeof(char));
    for (int i = 0; i < lists_counter; ++i) {
        lists[i] = (char *) calloc(64, sizeof(char));
    }

	char * path = get_tasks_path();

    // Go through files and add files to list
    if (directory = opendir(path)) {
        while ((entity = readdir(directory)) && (read_counter < lists_counter)) {
			char file_path[strlen(path)+70];
			strcpy(file_path, path);
			strcat(file_path, "/");
			strcat(file_path, entity->d_name);

			lstat(file_path, &file_info);

			if (entity && (S_ISREG(file_info.st_mode))) {
				strncpy(lists[read_counter], entity->d_name, strlen(entity->d_name)-5);
                read_counter = read_counter + 1;
			}
        }

        closedir(directory);

		free(path);

        return lists;
    }

	free(path);
}

void free_lists(char ** lists, int lists_counter) {
    for (int i = 0; i < lists_counter; ++i) {
        free(lists[i]);
    }
    
    free(lists);
}

char * read_list(char * list_name) {
    FILE * file;
    char * result;
    int result_size;

	char * path = get_tasks_path();
	char file_path[strlen(path)+strlen(list_name)+7];

    sprintf(file_path, "%s/%s.json", path, list_name);

    file = fopen(file_path, "r");

    fseek(file, 0, SEEK_END);

    result_size = ftell(file);

    rewind(file);

    result = (char *) calloc(result_size + 1, sizeof(char));

    fread(result, 1, result_size, file);

    result[result_size] = 0;

    fclose(file);
	free(path);

    return result;
}

void write_list(char * list_name, char * data) {
    FILE * file;

	char * path = get_tasks_path();
	char file_path[strlen(path)+strlen(list_name)+7];

    sprintf(file_path, "%s/%s.json", path, list_name);

    file = fopen(file_path, "w");

    fprintf(file, "%s", data);

    fclose(file);
	free(path);
}

void delete_list(char * list_name) {
	char * path = get_tasks_path();
	char file_path[strlen(path)+strlen(list_name)+7];

    sprintf(file_path, "%s/%s.json", path, list_name);

	remove(file_path);

	free(path);
}
