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

    if (!is_valid(sudo))
    {
        printf("The sudoku is not solvable\n");
        return 0;
    }
    if (!solve(sudo))
    {
        printf("The sudoku is not solvable\n");
        return 0;
    }
    to_file(sudo, *(argv+1));

    return 0;
}
