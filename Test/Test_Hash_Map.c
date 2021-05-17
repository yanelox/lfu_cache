#include "LFU.h"
#include <time.h>
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Hash_Int_Test ();
int Hash_Char_Test ();
int Init_Func_Test ();
int Test_SearchMap ();
//---------------------------------------------------------------------
//---------------------------------------------------------------------
static int pow_mod (int n, int k, int m) 
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
static int TestFreeHashMap (struct hash_map* Hash_Map) //Destructor of hash table
{
    struct hash_cell* del = NULL;
    for (int counter = 0; counter < Hash_Map->size; counter++)
    {
        del = Hash_Map->cells[counter]->next;
        if (del)
        {
            while (del->next)
            {
                free (del->item);
                del->item = NULL;
                del = del->next;
                free (del->prev);
            }
            free (del->item);
            del->item = NULL;
            free (del);
        }
    }

    for (int i = 0; i < Hash_Map->size; i++)
    {
        free (Hash_Map->cells[i]->item);
        Hash_Map->cells[i]->item = NULL;
        free (Hash_Map->cells[i]);
    }

    free (Hash_Map->cells);

    free (Hash_Map);
    return 0;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
static struct lfu_node* LfuNodeConstruct ()
{
    struct lfu_node* res = calloc (1, sizeof (struct lfu_node));
    assert (res);

    return res;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main ()
{
    int err = 0;
    err = Hash_Int_Test ();
    err = Hash_Char_Test ();
    err = Init_Func_Test ();
    err = Test_SearchMap ();

    return err;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Hash_Int_Test ()
{   
    FILE* f;
    int num_tests = 5;
    int number = 0;
    int cache_size = 0;
    int exp_h_int = 0;
    int h_int = 0;

    int prime = 2909;
    int coeff_1 = 211;
    int coeff_2 = 521;

    f = fopen ("HI.txt", "r");

    printf ("\t\t\t\t***Testing of HashofInt***\n\n");
    printf ("\t\t\t\t *Checking hand-made tests*\n");

    for (int i = 1; i <= num_tests; i++)
    {
        fscanf (f, "%d", &number);
        fscanf (f, "%d", &cache_size);

        fscanf (f, "%d", &exp_h_int);
        //exp_h_int = ((coeff_1 * number + coeff_2) % prime) % cache_size;
        h_int = HashofInt (number, cache_size);

        if (exp_h_int != h_int)
        {
            printf ("\t%d test falled:\n\tNumber = %d\n\tCache_size = %d\n\t\tWrong correspondence of expected result [%d] with gotten [%d]\n", i, number, cache_size, exp_h_int, h_int);
            continue;
        }
        printf ("\t\t#%d Test is OK\n", i);
        if (i == num_tests)
            printf ("\t\t\t\t    ***Tests passed***\n");
    }
    printf ("\n\t\t\t\t *Checking generated tests*\n");

    for (int i = 1; i <= num_tests; i++)
    {
        number = rand () % 4321;
        cache_size = rand () % 1234;

        exp_h_int = ((coeff_1 * number + coeff_2) % prime) % cache_size;
        h_int = HashofInt (number, cache_size);

        if (exp_h_int != h_int)
        {
            printf ("\t%d test falled:\n\tNumber = %d\n\tCache_size = %d\n\t\tWrong correspondence of expected result [%d] with gotten [%d]\n", i, number, cache_size, exp_h_int, h_int);
            continue;
        }
        printf ("\t\t#%d Test is OK\n", i);
        if (i == num_tests)
            printf ("\t\t\t\t    ***Tests passed***\n");
    }
    fclose (f);

    return 0;

}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Hash_Char_Test ()
{
    FILE* f;

    int num_tests = 5;
    int coeff = 241;
    int prime = 919;
    int exp_h_c = 0;
    int h_c = 0;
    char string[100] = {0};
    int len = 100;
    int cache_size = 0;
    int sum = 0;

    f = fopen ("HC.txt", "r");

    printf ("\n\t\t\t\t***Testing of HashofChar***\n\n");
    printf ("\t\t\t\t  *Checking hand-made tests*\n");

    for (int i = 0; i < num_tests; i++)
    {
        fscanf (f, "%d", &len);
        fscanf (f, "%s", string);
        fscanf (f, "%d", &cache_size);
        fscanf (f, "%d", &exp_h_c);

        h_c = HashofChar (string, len, cache_size);

       if (exp_h_c != h_c)
        {
            printf ("\t%d test falled:\n\tString = [%s]\n\tCache_size = %d\n\t\t"
                    "Wrong correspondence of expected result [%d] with gotten [%d]\n",
                    i + 1, string, cache_size, exp_h_c, h_c);
            continue;
        }
        printf ("\t\t#%d Test is OK\n", i + 1);
        if (i == num_tests)
            printf ("\t\t\t\t    ***Tests passed***\n");
    } 

    printf ("\n\t\t\t\t *Checking generated tests*\n");

    for (int i = 0; i < num_tests; i++)
    {   
        len = rand () % 100;
        for (int i = 0; i < len; i++)
            string[i] = (rand () % 94) + 32;
        cache_size = rand () % 427;

       for (int j = 0; j < len; j++)
        {
            sum += ( abs (string[j]) * pow_mod (coeff, len - j, prime)) % prime;
        }
        sum = sum % prime;

        exp_h_c = HashofInt (sum, cache_size);

        h_c = HashofChar (string, len, cache_size);

        sum = 0;

        if (exp_h_c != h_c)
        {
            printf ("\t%d test falled:\n\tString = [%s]\n\tCache_size = %d\n\t\t"
                    "Wrong correspondence of expected result [%d] with gotten [%d]\n", 
                    i + 1, string, cache_size, exp_h_c, h_c);
            continue;
        }
        printf ("\t\t#%d Test is OK\n", i + 1);
        if (i == num_tests)
            printf ("\t\t\t\t    ***Tests passed***\n");
    }

    fclose (f);
    return 0;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Init_Func_Test ()
{
    struct hash_map* test_map = NULL;  
    int cache_size = 0;
    int num_tests = 5;
    FILE* f;

    f = fopen ("INIT.txt", "r");

    printf ("\n\t\t\t\t***Testing of InitHashMap***\n\n");
    printf ("\t\t\t\t  *Checking hand-made tests*\n");

    for (int i = 1; i <= num_tests; i++)
    {
        fscanf (f, "%d", &cache_size);

        test_map = InitHashMap (cache_size);

        if (!test_map)
            printf ("\t%d test falled:\n\tCache_size = %d\n\t\t"
                    "InitHashMap returned null pointer\n",
                    i, cache_size);
        
        else if (!test_map->size)
            printf ("\t%d test falled:\n\tCache_size = %d\n\t"
                    "[test_map] = %p\n\t\t"
                    "Zero size of Hash_Map\n",
                    i, cache_size, test_map);
                    
        else if (!test_map->cells)
            printf ("\t%d test falled:\n\tCache_size = %d\n\t"
                    "[test_map] = %p\n\t\t"
                    "test_map->cells is a null-pointing array\n",
                    i, cache_size, test_map);

        else for (int counter = 0; counter < test_map->size; counter++)
            if (!test_map->cells[counter])
            {
                printf ("\t%d test falled:\n\tCache_size = %d\n\t"
                        "[test_map] = %p\n\t\t"
                        "test_map->cells[%d] is a null-pointing cell\n\t\t",
                        i, cache_size, test_map, counter);
            }
        for (int i = 0; test_map && i < test_map->size; i++)
            free (test_map->cells[i]);

        if (test_map)
            free (test_map->cells);

        free (test_map);
        
        printf ("\t\t#%d Test is OK\n", i);


        if (i == num_tests)
            printf ("\t\t\t\t    ***Tests passed***\n");
        
    }

    printf ("\n\t\t\t\t *Checking generated tests*\n");
    for (int i = 1; i <= num_tests; i++)
    {
        cache_size = rand () % 1000;

        test_map = InitHashMap (cache_size);

        if (!test_map)
            printf ("\t%d test falled:\n\tCache_size = %d\n\t\t"
                    "InitHashMap returned null pointer\n",
                    i, cache_size);
        
        else if (!test_map->size)
            printf ("\t%d test falled:\n\tCache_size = %d\n\t"
                    "[test_map] = %p\n\t\t"
                    "Zero size of Hash_Map\n",
                    i, cache_size, test_map);
                    
        else if (!test_map->cells)
            printf ("\t%d test falled:\n\tCache_size = %d\n\t"
                    "[test_map] = %p\n\t\t"
                    "test_map->cells is a null-pointing array\n",
                    i, cache_size, test_map);

        else for (int counter = 0; counter < test_map->size; counter++)
            if (!test_map->cells[counter])
            {
                printf ("\t%d test falled:\n\tCache_size = %d\n\t"
                        "[test_map] = %p\n\t\t"
                        "test_map->cells[%d] is a null-pointing cell\n\t\t",
                        i, cache_size, test_map, counter);
                break;
            }

        for (int i = 0; test_map && i < test_map->size; i++)
            free (test_map->cells[i]);
            
        if (test_map)
            free (test_map->cells);

        free (test_map);

        printf ("\t\t#%d Test is OK\n", i);
        if (i == num_tests)
            printf ("\t\t\t\t    ***Tests passed***\n");
    }

    fclose (f);
    return 0;
}

int Test_SearchMap ()
{
    FILE* f;
    struct hash_map* test_map = NULL;
    DATA* request = NULL;
    struct hash_cell* cell = NULL;    
    int cache_size = 123;
    int num_tests = 5;

    request = (DATA*) calloc (num_tests, sizeof (DATA));
    assert (request);

    test_map = InitHashMap (cache_size);
    
    f = fopen ("SF.txt", "r");

    printf ("\n\t\t\t\t***Testing of SearchMap***\n\n");
    printf ("\t\t\t\t  *Checking hand-made tests*\n");

    for (int i = 0; i < num_tests; i++)
    {
        fscanf (f, "%d", &((request + i)->data)); 

        cell = InsertHashMap (test_map, request + i);
        // exit (1);
        if (cell)
        {
            cell->item = LfuNodeConstruct ();
            cell->item->data_t = *(request + i);
        }
    }
    
    for (int i = 0; i < num_tests; i++)
    {
        cell = SearchMap (test_map, request + i);
        if (!cell)
            printf ("\t%d test falled:\n\tCache_size = %d\n\t\t"
                    "Function didn't find an element, but it's in Hash",
                    i, cache_size);
        if (cell->item->data_t.data != (request + i)->data)
            printf ("\t%d test falled:\n\tCache_size = %d\n\t\t"
                    "Function has found something else",
                    i, cache_size);

        else 
        {
            printf ("\t\t#%d Test is OK\n", i + 1);
            if (i == num_tests)
                printf ("\t\t\t\t    ***Tests passed***\n");
        }
    }

    printf ("\n\t\t\t\t *Checking generated tests*\n");

    for (int i = 0; i < num_tests; i++)
    {
        (request + i)->data = rand (); 

        cell = InsertHashMap (test_map, request + i);
        if (cell)
        {
            cell->item = LfuNodeConstruct ();
            cell->item->data_t = *(request + i);
        }

    }

    for (int i = 0; i < num_tests; i++)
    {
        cell = SearchMap (test_map, request + i);
        if (!cell)
            printf ("\t%d test falled:\n\tCache_size = %d\n\t\t"
                    "Function didn't find an element, but it's in Hash",
                    i, cache_size);
        if (cell->item->data_t.data != (request + i)->data)
            printf ("\t%d test falled:\n\tCache_size = %d\n\t\t"
                    "Function has found something else",
                    i, cache_size);

        else 
        {
            printf ("\t\t#%d Test is OK\n", i + 1);
            if (i == num_tests)
                printf ("\t\t\t\t    ***Tests passed***\n");
        }
    }

    fclose (f);  
    free (request);
    TestFreeHashMap (test_map);

    return 0;
}
