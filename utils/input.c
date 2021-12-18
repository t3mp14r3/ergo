#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../visual/visual.h"

char raw_input(char * preview) {
    system("/bin/stty raw");
    
    printf("%s", preview);

    OUTPUT_HIDE();
    char result = getchar();
    RESETF();

    system("/bin/stty cooked");

    return result;
}

char * input(char * preview, int length) {
    printf("%s", preview);

    length++;
    char * result = (char *) calloc(length, sizeof(char));

    fgets(result, length, stdin);
    
    char recovery;
    char *newline_search = strchr(result, '\n');
    if (newline_search) {
        *newline_search  = '\0';
    } else {
        while((recovery = getchar()) != '\n' && recovery != EOF);
    }

    return result;
}
