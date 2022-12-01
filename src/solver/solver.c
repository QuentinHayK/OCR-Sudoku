#include <stdio.h>
#include <stdlib.h>
#include "read_file.h"
#include "sudoku.h"


int Solve_Sudoku()
{
    char *sudo = malloc(81 * sizeof(char)+1);
    to_array("solver/test/easy1", sudo);

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

    printf("Sudoku solved\n");
    to_file(sudo, "solver/test/easy1");

    return 1;
}
