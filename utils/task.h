#ifndef TASK_H
#define TASK_H

#include <stdbool.h>

typedef struct Task {
   char * name;
   bool check;
} Task;

void check(char * list_name, char * task_name);
void delete_task(char * list_name, char * task_name);
#endif 
