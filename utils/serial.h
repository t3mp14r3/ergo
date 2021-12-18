#include "task.h"

void deserialise(char * json, Task ** tasks, int * len);
char * serialise(Task ** tasks, int len);
