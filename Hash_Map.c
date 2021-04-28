#include "Hash_Map.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_map Init_Hash_Map ()
{
    struct hash_map Hash_Map = {NULL, 0};
    
    Hash_Map.size = cache_size;


    Hash_Map.cells = (struct hash_cell*) calloc (cache_size, sizeof (struct hash_cell));    
    assert (Hash_Map.cells);

    for (int counter = 0; counter < cache_size; counter++)
    {
        // Hash_Map.cells[counter].next = (struct hash_cell*) calloc (1, sizeof (struct hash_cell));
        // assert (Hash_Map.cells[counter].next);

        // Hash_Map.cells[counter].item = (struct lfu_node*) calloc (1, sizeof (struct lfu_node));
        // assert (Hash_Map.cells[counter].item);
    }

    return Hash_Map;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Free_Hash_Map (struct hash_map Hash_Map)
{
    for (int counter = 0; counter < cache_size; counter++)
    {
        free (Hash_Map.cells[counter].next); 

        free (Hash_Map.cells[counter].item);
    }  
    free (Hash_Map.cells);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Insert_Hash_Map (struct hash_map* Hash_Map, int data)
{
    assert (Hash_Map);
    
    int key = Hash_of_Data (data);
    
    struct hash_cell* cell = Hash_Map->cells + key;
    struct hash_cell* start_cell = cell;

    //printf ("pcell = %p\n", cell->next);
    if (!cell->item)
    {
        cell->item = Lfu_Node_Constuct (cell->item);

        cell->item->data_t = data;
        return;
    }
    
    
    cell = Search_Data (cell, data);

    
    if (!cell)
    {
        cell = start_cell;
        while (cell->next)        
            cell = cell->next;

        cell->next = (struct hash_cell*) calloc (1, sizeof (struct hash_cell));
        assert (cell->next);

        cell->next->item = Lfu_Node_Constuct (cell->next->item);
        cell->next->item->data_t = data;
        return;
    }

}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Hash_of_Data (int data)
{
    int key = 0;

    int prime   = 2909;
    int coeff_1 = 211;
    int coeff_2 = 521;

    key = ((coeff_1 * data + coeff_2) % prime) % 2048;
    // printf ("CACHE_SIZE = %d", key);

    return key;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct lfu_node* Lfu_Node_Constuct (struct lfu_node* node)
{
    node = (struct lfu_node*) calloc (1, sizeof (struct lfu_node));
    assert (node);

    return node;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_cell* Search_Data (struct hash_cell* cell, int data)
{   
    while (cell->next)
    {
        if (!(cell->item->data_t - data))
            return cell;
        cell = cell->next;
    }
    if (!(cell->item->data_t - data))
            return cell;

    return NULL;
}