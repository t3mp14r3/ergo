#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <locale.h>

#include "../visual/visual.h"

// Handler function
void close_handler(int signal_message) {
    CURSOR_SHOW();
    RESETF();
    
    printf("\nClosing...\n");

    exit(0);
}

// Startup running function
void setup() {
    signal(SIGINT, close_handler);

    setlocale(LC_ALL, "");
}

// Closure function
void close() {
    CURSOR_SHOW();
    RESETF();
    CLEAR();

    printf("Closing...\n");

    exit(0);
}
