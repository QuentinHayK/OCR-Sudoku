char *check_nums(char *sudo, char *index)
{
    char i = index/9,
         j = index%9;

    char histo[9] = { 0 };

    for (char k; k<9; k+=1)
    {
        if (sudo[i*k+j] != '.')
        {
            histo[sudo[i*k+j] - 1] += 1;
        }

        if (sudo[i*9+k] != '.')
        {
            histo[sudo[i*9+k] - 1] += 1;
        }

        if (sudo[(x/3*3+k)*9 + (y/3*3+k%3)] != '.')
        {
            histo[sudo[(x/3*3+k)*9 + (y/3*3+k%3)] - 1]  += 1;
        }
    }

    return &histo;
}

char *AllPoss(char *sudo, char *index)
{
    char *histo = check_nums(sudo, index);
    char poss[10] = { 0 };
    char counter;

    for (char i; i<9; i+=1)
    {
        if (histo[i] == 0)
        {
            poss[counter] = i+1;
            counter += 1;
        }
    }

    return &poss;
}
