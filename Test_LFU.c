#include "LFU.h"
#include <time.h>
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void TestPageFunc (char* file)
{
    
    assert (file);

    FILE* f;

    if (strcmp (file, "stdout") == 0)
        f = stdout;

    else
        f = fopen (file, "w");

    int count  = 10000000;

    DATA* pages = calloc (count, sizeof (DATA));


    printf ("Randomly generated pages\n");

    for (int i = 0; i < count; ++i)
        pages[i].data = rand () % 10000;
    
    for (int i = 0; i < count; ++i)
        CPrintPage (pages + i);


    free (pages);

    if (strcmp (file, "stdout"))
        fclose (f);   
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void TestLFUFunc (char* file)
{
    assert (file);

    FILE* f;

    if (strcmp (file, "stdout") == 0)
        f = stdout;

    else
        f = fopen (file, "w");

    int count  = 10000000;

    DATA* pages = calloc (count, sizeof (DATA));
    LFU* cache  = LfuConstruct (128);

    printf ("Randomly generated pages\n");

    for (int i = 0; i < count; ++i)
        pages[i].data = rand () % 10000;
    
    // for (int i = 0; i < count; ++i)
    //     CPrintPage (pages + i);

    time_t start = time (NULL);

    for (int i = 0; i < count; ++i)
        InsertLFU (cache, pages + i);

    start = time(NULL) - start;

    printf ("%ld\n", start);

    FreeLFU (cache);

    free (pages);

    if (strcmp (file, "stdout"))
        fclose (f);
}