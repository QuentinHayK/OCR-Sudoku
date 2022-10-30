#include <stdio.h>
#include <stdlib.h>
#include "read_file.h"
#include "sudoku.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        return 1;
    }

    char *sudo = malloc(81 * sizeof(char)+1);

    to_array(*(argv+1), sudo);

    print_sudo(sudo);
    printf("\n");

    solve(sudo);

    print_sudo(sudo);

    return 0;
}
