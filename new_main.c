#include "LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main (int argc, char* argv[])
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


    int cache_size = 0;
    int count_pages = 0;
    int cache_fullness = 0;

    fscanf (input, "%d%d", &cache_size, &count_pages);


    DATA* input_page = calloc(1, sizeof (DATA));

    struct hash_map* HashTable = Init_Hash_Map (cache_size);

    struct freq_node* List = create_head ();


    for (int i = 0; i < count_pages; ++i)
    {
        input_page = GetPage (input);

        struct hash_cell* found_cell = Search_Map (HashTable, input_page);

        if (!found_cell)
        {
            ++cache_fullness;

            if (cache_fullness > cache_size)
            {
                remove_lfu (List);

                //TODO: add removing from hash taable

                --cache_fullness;
            }

            struct lfu_node* created_lfu = create_lfu (*input_page, List);

            struct hash_cell* created_cell = Insert_Hash_Map (HashTable, input_page);

            created_cell->item = created_lfu;
        }

        else
        {
            replace_lfu (found_cell->item);
        }
    }


    free (input_page);

    if (strcmp (argv[1], "stdin") != 0)
        fclose (input);
}