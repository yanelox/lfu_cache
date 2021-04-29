#include "Hash_Map.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main ()
{
    struct hash_map* Hash_Map = NULL;
    Hash_Map = Init_Hash_Map ();

    for (int i = 0; i < NUM; i++)
        Insert_Hash_Map (Hash_Map, i);

    //int res = Hash_of_Data (NUM / 2);
    //printf ("RES = %d\n", res);

    //printf ("Hash_Map.cells[670].items->data_t = %d\n", Hash_Map->cells[res].item->data_t);

    // struct hash_cell* test = Hash_Map->cells[res].next->next;
    // printf ("data = %d\n", test->prev->prev->item->data_t);
    //Test_Hash_Map (Hash_Map);
    Free_Hash_Map (Hash_Map);

    
}
//TODO: idea for test: print all collisions list
//TODO: tests for all func
