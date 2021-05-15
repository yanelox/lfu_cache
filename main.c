#include "LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main ()
{
    struct hash_map* Hash_Map = NULL;
    struct hash_cell* cell = NULL;
    DATA* requests = NULL;
    int cache_size = 100;
    Hash_Map = Init_Hash_Map (cache_size);

    requests = (DATA*) calloc (NUM, sizeof (DATA));

    for (int i = 0; i < NUM; i++)
    {
        requests[i].data = i;
    }
    int res;
    
    for (int i = 0; i < NUM; i++)
    {   
        Insert_Hash_Map (Hash_Map, requests + i);
    }
    
    for (int i = 0; i < NUM; i++)
    {   
        Del_Elem (Hash_Map, requests + i);
    }
    
    Free_Hash_Map (Hash_Map);

    free (requests);
    
}
//TODO: idea for test: print all collisions list
//TODO: tests for all func
