#include <err.h>
#include <stdio.h>
#include <stdlib.h>

void print_sudo(char *sudoku)
{
    printf("///////////////////////\n");
    char i = 1;
    printf("%c", *sudoku);
    while (i<81)
    {
        if (i%3 == 0)
        {
            if (i%27 == 0)
                printf("\n");
            if (i%9 == 0)
                printf("\n");
            else
                printf(" ");
        }
        printf("%c", *(sudoku+i));
        i+=1;
    }
    printf("\n");
}


char search_empty_case(char *sudo)
{
    char i = 0;
    while (i<81 && *(sudo+i) != '.')
    {
        i+=1;
    }

    return i;
}


char *check_index(char *sudo, char index)
{
    char x = index/9,
         y = index%9,
         var = 0;

    char *histo = calloc(10, sizeof(char));
    if (histo == NULL)
        errx(1, "Not enough memory!");

    for (char k=0; k<9; k+=1)
    {
        var = *(sudo+k*9+y);
        if (var != '.')
            *(histo+var-'0'-1) += 1;

        var = *(sudo+x*9+k);
        if (var != '.')
            *(histo+var-'0'-1) += 1;

        var = *(sudo+ (x/3*3+k/3)*9 + (y/3*3+k%3));
        if (var != '.')
            *(histo+var-'0'-1) += 1;
    }
    return histo;
}


char *all_poss(char *sudo, char index)
{
    char *histo = check_index(sudo, index);
    char *poss = calloc(10, sizeof(char));
    if (poss == NULL)
        errx(1, "Not enough memory!");

    char *ptr = poss;

    for (char i=0; i<9; i+=1)
    {
        if (*(histo+i) == 0)
        {
            *ptr = i+1;
            ptr += 1;
        }
    }
    free(histo);

    return poss;
}


char solve(char *sudo)
{
    char index = search_empty_case(sudo);
    if (index == 81)
        return 1;

    char *poss = all_poss(sudo, index);

    char i = 0;
    char solved = 0;
    while (*(poss+i) != 0 && !solved)
    {
        *(sudo+index) = '0' + *(poss+i);
        solved = solve(sudo);

        if (!solved)
            *(sudo+index) = '.';
        i+=1;
    }
    free(poss);
    return solved;
}
