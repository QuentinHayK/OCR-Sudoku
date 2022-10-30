#include <stdio.h>
#include <err.h>

void to_array(char *way, char *sudo)
{
    FILE* fs = fopen(way, "r");

    if (fs == NULL)
        errx(1, "%s can't be opened\n", way);

    char *ptr = sudo;
    char c;

    while (!feof(fs))
    {
        c = fgetc(fs);
        if (c != ' ' && c != '\n')
        {
            *ptr = c;
            ptr += 1;
        }
    }

    fclose(fs);
}

void to_file(char *sudo, char *way)
{
    FILE *fs = fopen(way);
    char i = 1;

    fputc(*sudo, fs);
    while (!(sudo+i) != 0)
    {
        fputc(*(sudo+i), fs);
        if (i%3 == 0)
        {
            if (i%9 == 0)
                fputc('\n', fs);
            else
                fputc(' ', fs);

            if (i%27 == 0)
                fputc('\n', fs);
        }
        i += 1;
    }
    fclose(fs);
}
