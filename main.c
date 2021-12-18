#include <stdlib.h>

#include "./utils/setup.h"
#include "./modules/modules.h"

int main(int argc, char * argv[]) {
    // Run the setup process
	setup();

	// Start the main menu
	menu();

    return 0;
}
