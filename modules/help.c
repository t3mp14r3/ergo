#include <stdio.h>
#include "../visual/visual.h"
#include "../utils/input.h"

void help_menu() {
	CLEAR();

	printf(BOLD "\n\n    Help:\n\n" RESET);

	printf("    j      go down\n");
	printf("    k      go up\n");
	printf("    enter  select list\n");
	printf("    n      create list\n");
	printf("    d      delete list\n");
	printf("    r      rename list\n");
	printf("    q      quit\n\n");

	printf(DIM);
	raw_input("    Press any key to continue...");
	RESETF();

	CLEAR();
}

void help_open() {
	CLEAR();

	printf(BOLD "\n\n    Help:\n\n" RESET);

	printf("    j      go down\n");
	printf("    k      go up\n");
	printf("    space  check/uncheck\n");
	printf("    enter  check/uncheck\n");
	printf("    r      edit task\n");
	printf("    n      new task\n");
	printf("    d      delete\n");
	printf("    q      quit to menu\n\n");

	printf(DIM);
	raw_input("    Press any key to continue...");
	RESETF();

	CLEAR();
}
