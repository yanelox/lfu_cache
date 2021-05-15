#include "LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main (int argc, char* argv[]) //kekw
{
    assert (argc);

    if (argc != 2)
    {
        printf ("Incorrect args\n");
        return 0;
    }

    FILE* input = NULL;

    if (strcmp (argv[1], "stdin") == 0)
        input = stdin;

    else
        input = fopen (argv[1], "r");


    int cache_sizze = 0;
    int count_pages = 0;

    fscanf (input, "%d%d", &cache_sizze, &count_pages);


    DATA* input_page = calloc(1, sizeof (DATA));

    struct hash_map* HashTable = Init_Hash_Map (cache_sizze);

    struct freq_node* List = create_head ();


    for (int i = 0; i < count_pages; ++i)
        ;


    free (input_page);

    if (strcmp (argv[1], "stdin") != 0)
        fclose (input);
}