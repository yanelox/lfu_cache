#include "LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
DATA GetPage (FILE* f)
{
    assert (f);

    DATA res = {0};

    assert (fscanf (f, "%d", &res.data) == 1);

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

    fprintf (f, "===\n");
    fprintf (f, "%d\n", page->data);
    fprintf (f, "===\n");
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
LFU* LfuConstruct (int cache_size)
{
    LFU* res = calloc (1, sizeof (LFU));

    assert (res);

    res->HashTable = Init_Hash_Map (cache_size);
    res->List      = create_head   ();

    res->cache_size    = cache_size;
    res->cache_fullnes = 0;

    return res; 
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void InsertLFU (LFU* cache, DATA* request)
{
    assert (cache);
    assert (request);

    struct hash_cell* found_cell = Search_Map (cache->HashTable, request);
        
    if (!found_cell)
    {
        cache->cache_fullnes++;

        if (cache->cache_fullnes > cache->cache_size)
        {
            Del_Elem (cache->HashTable, &cache->List->next->child->data_t); // we should delete elem with
                                                                            // the lowest frequency        
            remove_lfu (cache->List);

            cache->cache_fullnes--;
        }

        struct lfu_node* created_lfu = create_lfu (*request, cache->List);

        struct hash_cell* created_cell = Insert_Hash_Map (cache->HashTable, request);

        created_cell->item = created_lfu;
    }

    else
    {
        replace_lfu (found_cell->item);
    }
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void FreeLFU (LFU* cache)
{
    assert (cache);

    Free_Hash_Map (cache->HashTable);

    struct freq_node* node = cache->List;
    struct freq_node* tmp_node = cache->List;

    while (node)
    {
        tmp_node = node;
        node = node->next;
        free (tmp_node);
    }

    free (cache);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void LFUDump (LFU* cache)
{
    assert (cache);

    printf ("===\n");
    printf ("HashTable = %p\n", cache->HashTable);  //hashtable dump
    printf ("Frequency list = %p\n", cache->List);  //listdump
    printf ("Cache capacity = %d\n", cache->cache_size);
    printf ("Cache fullness = %d\n", cache->cache_fullnes);
    printf ("===\n");
}