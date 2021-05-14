#include "LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
DATA* GetPage (char* source)
{
    assert (source);

    FILE* f = NULL;
    DATA* res =  calloc (1, sizeof (DATA));

    if (strcmp (source, "stdin") == 0)
        f = stdin;

    else
        f = fopen (source, "r");

    fscanf (f, "%d", &res->data);
    fscanf (f, "%f", &res->d);

    return res;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void PrintPage (DATA* page, char* source)
{
    assert (page);
    assert (source);

    FILE* f = NULL;

    if (strcmp (source, "stdout") == 0)
        f = stdout;

    else
        f = fopen (source, "w");

    fprintf (f, "==========\n");
    fprintf (f, "%d\n", page->data);
    fprintf (f, "%f\n", page->d);
    fprintf (f, "==========\n");
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------