#include "Hash_Map.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main ()
{
    struct hash_map* Hash_Map = NULL;
    DATA** requests = NULL;
    Hash_Map = Init_Hash_Map ();

    requests = (DATA**) calloc (NUM, sizeof (DATA*));

    for (int i = 0; i < NUM; i++)
    {
        requests[i] = (DATA*) calloc (1, sizeof (DATA));
        requests[i]->data = i;
        requests[i]->c = 'c';
        requests[i]->d = (float) i / 232;
      
    }
    
    for (int i = 0; i < NUM; i++)
        Insert_Hash_Map (Hash_Map, requests[i]);
    

    int res = Hash_of_Data (requests[NUM / 2 + 1]);
    printf ("RES = %d\n", res);

    printf ("Hash_Map.cells[%d].items->data_t = %d\nHash_Map.cells[%d].items->c = %c\nHash_Map.cells[%d].items->d = %f", res, Hash_Map->cells[res].item->data_t->data, res, Hash_Map->cells[res].item->data_t->c, res, Hash_Map->cells[res].item->data_t->d);

    // struct hash_cell* test = Hash_Map->cells[res].next->next;
    // printf ("data = %d\n", test->prev->prev->item->data_t);
    //Test_Hash_Map (Hash_Map);
    Free_Hash_Map (Hash_Map);

   for (int i = 0; i < NUM; i++)
        free (requests[i]);
    
    free (requests);
    

    
}
//TODO: idea for test: print all collisions list
//TODO: tests for all func
