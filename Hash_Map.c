#include "LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
static int pow_mod (int n, int k, int m) //This is just an auxiliary function
{
  int mult = 0, prod = 0;

  if (n == 0 || n == 1 || k == 1)
    return n;
  if (k == 0)
    return 1;

  mult = n;
  prod = 1;
  while (k > 0)
  {
    if ((k % 2) == 1)
      prod = (prod * mult) % m;
    mult = (mult * mult) % m;
    k = k / 2;
  }
  return prod;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_map* Init_Hash_Map () //Constructor of hash table
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
int Free_Hash_Map (struct hash_map* Hash_Map) //Destructor of hash table
{
    struct hash_cell* del = NULL;
    for (int counter = 0; counter < cache_size; counter++)
    {
        del = Hash_Map->cells[counter].next;
        if (del)
        {
            while (del->next)
            {
                del = del->next;
                free (del->prev);

            }
            free (del);
        }
    }

    free (Hash_Map->cells);

    free (Hash_Map);
    return 0;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Insert_Hash_Map (struct hash_map* Hash_Map, DATA* request)
{
    assert (Hash_Map); //TODO: exception catcher

    int key = Hash_of_Data (request);
    struct hash_cell* cell = Hash_Map->cells + key;
    struct hash_cell* start_cell = cell;

    if (!cell->item)
    {
        cell->item = Lfu_Node_Constuct ();

        cell->item->data_t = request;
        return 0;
    }

    cell = Search_Data (cell, request);

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
        cell->next->item = Lfu_Node_Constuct ();
        cell->next->item->data_t = request;
        return 0;
    }
    return 0;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Hash_of_Data (DATA* request)
{
    int key = 0;
    char* string = NULL;
    size_t req_size = sizeof (*request); //size of request

    string = (char*) calloc (req_size, sizeof (char));
    string = memcpy (string, request, req_size);
    
    key = Hash_of_Char (string, req_size);
    free (string);

    return key;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Hash_of_Int (int number)
{
  int prime = 2909;
  int coeff_1 = 211;
  int coeff_2 = 521;

  int h_int = 0;

  h_int = ((coeff_1 * number + coeff_2) % prime) % cache_size;

  return h_int;

}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Hash_of_Char (char* string, int len)
{
  int h_c = 0;
  int coeff = 241;
  int prime = 919;
  int sum = 0;

  for (int i = 0; i < len; i++)
  {
    sum += ( abs (string[i]) * pow_mod (coeff, len - i, prime)) % prime;
  }
  sum = sum % prime;

  h_c = Hash_of_Int (sum);

  return h_c;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct lfu_node* Lfu_Node_Constuct () 
{   
    struct lfu_node* node = NULL;

    node = (struct lfu_node*) calloc (1, sizeof (struct lfu_node));
    assert (node);

    return node;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_cell* Search_Data (struct hash_cell* cell, DATA* request)
{
    while (cell->next)
    {
        if (cell->item->data_t == request)
            return cell;

        cell = cell->next;
    }
    //In the next line I try to find an element in the last node of the list
    if (cell->item->data_t == request)
            return cell;

    return NULL;
}
//TODO: print table func :)
// int Test_Hash_Map (struct hash_map* Hash_Map)
// {
//     FILE* fp;
//     int res = 0;
//     struct hash_cell cell;
//     struct hash_cell* cell_next = NULL;

//     const char* name = "text.map";
    
//     fp = fopen (name, "w");

//     for (int i = 0; i < NUM; i++)
//     {
 
//         fprintf (fp, "#%d\n\tdata:\n", i);
        
//         res = Hash_of_Data (i);
//         cell = Hash_Map->cells[res];

//         if (cell.next)
//             cell_next = cell.next;

//         if (cell.item)
//             fprintf (fp, "\t\t%d\n", cell.item->data_t);

//         while (cell_next)
//         {
//             if (cell_next->item)
//                 fprintf (fp, "\t\t%d\n", cell_next->item->data_t);
//             cell_next = cell_next->next;
//         }
//     }

//     fclose (fp);
// }

