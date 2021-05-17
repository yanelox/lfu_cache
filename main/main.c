#include "LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main ()
{
    struct hash_map* Hash_Map = NULL;
    DATA* requests = NULL;
    int cache_size = 100;
    Hash_Map = InitHashMap (cache_size);

    requests = (DATA*) calloc (NUM, sizeof (DATA));

    for (int i = 0; i < cache_size; i++)
    {
        requests[i].data = i;
    }
    
    for (int i = 0; i < NUM; i++)
    {   
        InsertHashMap (Hash_Map, requests + i);
    }

    // PrintHashMap (Hash_Map);
    
    for (int i = 0; i < NUM; i++)
    {   
        DelElem (Hash_Map, requests + i);
    }
    
    FreeHashMap (Hash_Map);

    free (requests);
    
}
//TODO: idea for test: print all collisions list
//TODO: tests for all func
