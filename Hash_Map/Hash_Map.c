#include "../LFU/LFU.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//Params: integer number, power to number, modulo (number, power, mod)
//  This function recieves integer number and raise it to a power modulo mod
//Returned value: The result of operation
//---------------------------------------------------------------------
//---------------------------------------------------------------------
static int pow_mod (int number, int power, int mod) //This is just an auxiliary function
{
    int mult = 0, prod = 0;

    if (number == 0 || number == 1 || power == 1)
        return number;
    if (power == 0)
        return 1;

    mult = number;
    prod = 1;
    while (power > 0)
    {
        if ((power % 2) == 1)
        prod = (prod * mult) % mod;
        mult = (mult * mult) % mod;
        power = power / 2;
    }
    return prod;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_map* InitHashMap (int cache_size) 
{
    if (cache_size < 0)
        return NULL;

    struct hash_map* Hash_Map = (struct hash_map*) calloc (1, sizeof (struct hash_map));
    assert (Hash_Map);

    Hash_Map->size = cache_size / 10 + 1; //number of collisions

    Hash_Map->cells = (struct hash_cell**) calloc (Hash_Map->size, sizeof (struct hash_cell*));
    assert (Hash_Map->cells);

    for (int counter = 0; counter < Hash_Map->size; counter++)
    {
        Hash_Map->cells[counter] = (struct hash_cell*) calloc (1, sizeof (struct hash_cell));
        assert (Hash_Map->cells[counter]); 
    }

    return Hash_Map;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int FreeHashMap (struct hash_map* Hash_Map) //Destructor of hash table
{
    struct hash_cell* del = NULL;
    for (int counter = 0; counter < Hash_Map->size; counter++)
    {
        del = Hash_Map->cells[counter]->next;
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

    for (int i = 0; i < Hash_Map->size; i++)
        free (Hash_Map->cells[i]);

    free (Hash_Map->cells);

    free (Hash_Map);
    return 0;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_cell* InsertHashMap (struct hash_map* Hash_Map, DATA* request)
{
    assert (Hash_Map);

    int key = HashofData (request, Hash_Map->size);
    struct hash_cell* cell = Hash_Map->cells[key];
    struct hash_cell* start_cell = cell;

    if (!cell->item)
    {
        return cell;
    }

    cell = SearchData (cell, request);

    if (!cell)
    {
        cell = start_cell;
        while (cell->next)
        {
            cell->next->prev = cell;
            cell = cell->next;
        }

        cell->next = (struct hash_cell*) calloc (1, sizeof (struct hash_cell));
        assert (cell->next);
    

        cell->next->prev = cell;
    
        return cell->next;
    }
    
    return NULL;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int HashofData (DATA* request, int hash_size)
{
    int key = 0;
    char* string = NULL;
    size_t req_size = sizeof (*request); //size of request

    string = (char*) calloc (req_size, sizeof (char));
    string = memcpy (string, request, req_size);

   
    key = HashofChar (string, req_size, hash_size);
    free (string);
     
    return key;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int HashofInt (int number, int hash_size)
{
    int prime = 2909;
    int coeff_1 = 211;
    int coeff_2 = 521;

    int h_int = 0;

    h_int = ((coeff_1 * number + coeff_2) % prime) % hash_size;

    return h_int;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int HashofChar (char* string, int len, int hash_size)
{
    int h_c = 0;
    int coeff = 241;
    int prime = 919;
    int sum = 0;

    for (int i = 0; i < len; i++)
    {
        sum += ( abs (string[i]) * pow_mod (coeff, len - i, prime)) % prime + 1;
    }
    sum = sum % prime;

    h_c = HashofInt (sum, hash_size);

    return h_c;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_cell* SearchData (struct hash_cell* cell, DATA* request)
{
    while (cell->next)
    {
        if (cell->item->data_t.data == request->data)   
            return cell;

        cell = cell->next;
    }
    //In the next line I try to find an element in the last node of the list
    
    if (cell->item && cell->item->data_t.data == request->data)
            return cell;
    
    return NULL;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_cell* SearchMap (struct hash_map* Hash_Map, DATA* request)
{
    int key = HashofData (request, Hash_Map->size);
    
    struct hash_cell* cell = Hash_Map->cells[key];

    if (!cell->item)
        return NULL;

    cell = SearchData (cell, request);

    return cell;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int DelElem (struct hash_map* Hash_Map, DATA* request)
{
    int key = HashofData (request, Hash_Map->size);
    struct hash_cell* cell = SearchMap (Hash_Map, request);
    
    if (!cell)
    {
        return 0;
    }

    if (!cell->prev)
    {
        
        if (cell->next)
        { 
            Hash_Map->cells[key] = cell->next;

            Hash_Map->cells[key]->prev = NULL;
            
            free (cell);
        }

        else
        {
            Hash_Map->cells[key]->item = NULL;
        }
           
        return 0;
    }

    if (cell->next)
        cell->next->prev = cell->prev;

    cell->prev->next = cell->next;
    
    free (cell);

    return 0;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int PrintHashMap (struct hash_map* Hash_Map, FILE* f)
{
    assert (Hash_Map);

    struct hash_cell* cell;

    for (int i = 0; i < Hash_Map->size; i++)
    {
        fprintf (f, "===\n%d)\n", i);
        
        cell = Hash_Map->cells[i];

        while (cell)
        {
            if (cell->item)
                fprintf (f, "%d ", cell->item->data_t.data);

            cell = cell->next;
        }

        fprintf (f, "\n");
    }
    return 0;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
