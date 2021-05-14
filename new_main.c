#include "LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main ()
{
    int count_pages = 0;

    scanf ("%d", &count_pages);

    DATA** pages = calloc (count_pages, sizeof (DATA*));

    for (int i = 0; i < count_pages; ++i)
        pages[i] = CGetPage();

    for (int i = 0; i < count_pages; ++i)
        CPrintPage (pages[i]);

    for (int i = 0; i < count_pages; ++i)
        free (pages[i]);

    free (pages);
}