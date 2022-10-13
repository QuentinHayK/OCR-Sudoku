#include <stdio.h>

char *to_array(char *way)
{
    FILE* fs;

    fs = fopen(way, "r");

    if (fs == NULL) {
        printf("%s can't be opened\n", way);
        return NULL;
    }

    char buffer[121];
    while (fscanf(fs, "%*s", buffer)) {
        printf("%s", buffer)
    }
    return buffer;
}
