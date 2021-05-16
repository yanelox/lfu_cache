#include "LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void TestPageFunc (char* file)
{
    printf ("Page reading and printing tests\n");

    FILE* f = fopen (file, "r");

    assert (f);

    int count = 0;
    assert (fscanf (f, "%d", &count) == 1);

    DATA* pages = calloc (count, sizeof (DATA));
    assert (pages);

    for (int i = 0; i < count; ++i)
        pages[i] = GetPage (f);

    fclose (f);

    for (int i = 0; i < count; ++i)
        CPrintPage (pages + i);

    printf ("Randomly generated pages\n");

    for (int i = 0; i < count; ++i)
        pages[i].data = rand () % 1000;
    
    for (int i = 0; i < count; ++i)
        CPrintPage (pages + i);

    free (pages);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void TestLFUFunc (char* file)
{
    printf ("Test LFUConstruct, LFUDump and FreeLFU funcs with reading cache sizes from file\n");

    FILE* f = fopen (file, "r");

    assert (f);

    int count = 0;
    assert (fscanf (f, "%d", &count) == 1);    

    int* sizes = calloc (count, sizeof (int));
    assert (sizes);

    for (int i = 0; i < count; ++i)
        assert (fscanf (f, "%d", sizes + i) == 1);

    LFU** caches = calloc (1, sizeof (LFU*));
    assert (caches);

    // for (int i = 0; i < count; ++i)
    // {
    //     caches[i] = LfuConstruct (sizes[i]);
    //     assert (caches[i]);
    // }

    // for (int i = 0; i < count; ++i)
    //     LFUDump (caches[i]);

    // for (int i = 0; i < count; ++i)
    //     FreeLFU (caches[i]);

    free (sizes);
    free (caches);
    fclose (f);
}