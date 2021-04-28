#include "Hash_Map.h" //TODO: change int to typedef
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_map* Init_Hash_Map ()
{
    struct hash_map* Hash_Map = (struct hash_map*) calloc (1, sizeof (struct hash_map));
    assert (Hash_Map);

    Hash_Map->size = cache_size;

    Hash_Map->cells = (struct hash_cell*) calloc (cache_size, sizeof (struct hash_cell));
    assert (Hash_Map->cells); //TODO: exception catcher 1111

    return Hash_Map;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Free_Hash_Map (struct hash_map* Hash_Map)
{
    struct hash_cell* del = NULL;
    for (int counter = 0; counter < cache_size; counter++)
    {
        del = Hash_Map->cells[counter].next;
        while (del->next)
        {
            free (del->item);
            del = del->next;
            free (del->prev);

        }
        free (del->item);
        free (del);
        free (Hash_Map->cells[counter].item);
    }

    free (Hash_Map->cells);

    free (Hash_Map);
    return 0;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Insert_Hash_Map (struct hash_map* Hash_Map, int data)
{
    assert (Hash_Map); //TODO: exception catcher

    int key = Hash_of_Data (data);

    struct hash_cell* cell = Hash_Map->cells + key;
    struct hash_cell* start_cell = cell;

    if (!cell->item)
    {
        cell->item = Lfu_Node_Constuct (cell->item);

        cell->item->data_t = data;
        return 0;
    }

    cell = Search_Data (cell, data);

    if (!cell)
    {
        cell = start_cell;
        while (cell->next)
        {
            cell->next->prev = cell;
            cell = cell->next;
        }

        cell->next = (struct hash_cell*) calloc (1, sizeof (struct hash_cell));
        assert (cell->next); //TODO: exception catcher

        cell->next->prev = cell;
        cell->next->item = Lfu_Node_Constuct (cell->next->item);
        cell->next->item->data_t = data;
        return 0;
    }
    return 0;
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

    return key;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct lfu_node* Lfu_Node_Constuct (struct lfu_node* node) //TODO: remove ndoe from func args
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
        if (cell->item->data_t == data)
            return cell;

        cell = cell->next;
    }
    //In the next line I try to find an element in the last node of the list
    if (cell->item->data_t == data)
            return cell;

    return NULL;
}
//TODO: print table func
