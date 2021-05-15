#include "LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main ()
{
    struct hash_map* Hash_Map = NULL;
    DATA* requests = NULL;
    int cache_size = 15;
    Hash_Map = Init_Hash_Map (cache_size);

    requests = (DATA*) calloc (NUM, sizeof (DATA));

    for (int i = 0; i < NUM; i++)
    {
        requests[i].data = i;
    }
    int res;
    
    for (int i = 0; i < NUM; i++)
    {   
        scanf ("%d", &res);
        (requests + i)->data = res; 
        // printf ("%d\n", i);
        Insert_Hash_Map (Hash_Map, requests + i);

        if (res == 666)
            break;
    }
    
    printf ("%d\n", sizeof (struct lfu_node));

    res = Hash_of_Data (requests + (NUM / 2 + 1), cache_size);
    //printf ("RES = %d\n", res);

    

    // struct hash_cell* test = Hash_Map->cells[res].next->next;
    // printf ("data = %d\n", test->prev->prev->item->data_t);
    //Test_Hash_Map (Hash_Map);
    Free_Hash_Map (Hash_Map);

    free (requests);
    

    
}
//TODO: idea for test: print all collisions list
//TODO: tests for all func
