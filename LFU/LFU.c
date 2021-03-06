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
    if (cache_size < 0)
        return NULL;

    LFU* res = calloc (1, sizeof (LFU));

    assert (res);

    res->HashTable = InitHashMap (cache_size);
    res->List      = CreateHead   ();

    res->cache_size    = cache_size;
    res->cache_fullnes = 0;

    return res; 
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int InsertLFU (LFU* cache, DATA* request)
{   
    int res = 0;

    assert (cache);
    assert (request);

    struct hash_cell* found_cell = SearchMap (cache->HashTable, request);
    
    if (!found_cell)
    {
        cache->cache_fullnes++;

        if (cache->cache_fullnes > cache->cache_size)
        {
            DelElem (cache->HashTable, &cache->List->next->child->data_t); // we should delete elem with
                                                                            // the lowest frequency        
            RemoveLfu (cache->List);

            cache->cache_fullnes--;
        }
        
        struct lfu_node* created_lfu = CreateLfu (*request, cache->List);

        struct hash_cell* created_cell = InsertHashMap (cache->HashTable, request);
        
        created_cell->item = created_lfu;             
    }

    else
    {
        ReplaceLfu (found_cell->item);
        res = 1;
    }

    return res;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void FreeLFU (LFU* cache)
{
    assert (cache);

    FreeHashMap (cache->HashTable);

    DeleteList (cache->List);

    free (cache);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void LFUDump (LFU* cache, char* source)
{
    assert (cache);

    FILE* f;

    if (strcmp (source, "stdout") == 0)
        f = stdout;

    else
    {
        f = fopen (source, "w");

        assert (f);
    }

    fprintf (f, "===\n");
    fprintf (f, "HashTable:\n");
    PrintHashMap (cache->HashTable, f);
    fprintf (f, "===\n");
    fprintf (f, "List:\n");
    ListPrint (cache->List, f);
    fprintf (f, "===\n");
    fprintf (f, "Cache capacity = %d\n", cache->cache_size);
    fprintf (f, "Cache fullness = %d\n", cache->cache_fullnes);
    fprintf (f, "===\n");
}