#ifndef SUDOKU
#define SUDOKU

char search_empty_case(char *sudo);
char *check_index(char *sudo, char *index);
char *all_poss(char *sudo, char index);
char solve(char *sudo);
void print_sudo(char *sudoku);

#endif
