#include "LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main (int argc, char* argv[])
{
    assert (argc);

    if (argc > 2)
    {
        printf ("Incorrect args\n");
        return 0;
    }

    FILE* input = NULL;

    if (argc == 1 || strcmp (argv[1], "stdin") == 0)
        input = stdin;

    else
        input = fopen (argv[1], "r");


    int cache_size = 0;
    int count_pages = 0;
    int count_hit = 0;

    fscanf (input, "%d%d", &cache_size, &count_pages);


    DATA* input_page = calloc(1, sizeof (DATA));

    LFU* Cache = LfuConstruct (cache_size);

    for (int i = 0; i < count_pages; ++i)
    {
        *input_page = GetPage (input);

        count_hit += InsertLFU (Cache, input_page);
    }

    LFUDump (Cache, "stdout");

    printf ("count hits = %d\n", count_hit);

    FreeLFU (Cache);

    free (input_page);

    if (strcmp (argv[1], "stdin") != 0)
        fclose (input);
}