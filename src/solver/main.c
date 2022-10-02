#include <stdio.h>
#include "read_file.h"

int main(int argc, char *argv)
{
    if (argc != 2) {
        return 1;
    }

    to_array(argv[1]);
    return 0;
}
