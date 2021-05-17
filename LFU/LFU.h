#pragma once
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#define NUM 100
//---------------------------------------------------------------------
//---------------------------------------------------------------------
typedef struct request_t DATA;
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct request_t      //change it like you want
{
    int               data;
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
// List part
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct lfu_node;
struct freq_node;
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Creates an element in the place the user wants. 
    Function need data(frequency) and previous item (place where we should create)

    @param [in] freq_dat Frequency node
    @param [in] prev_fr Previous item (lfu node)

    @return Pointer to element which was created
*/
struct freq_node* CreateFreq(int freq_dat, struct freq_node* prev_fr);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Creates last lfu_node at frequency 1. 
    If frequency 1 is not exist, it will  be created (with function create_freq).

    @param [in] lfu_dat Page with data which well be added to lfu_node
    @param [in] head Head of list

    @return Pointer to node which was created
*/
struct lfu_node* CreateLfu(DATA lfu_dat, struct freq_node* head);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Delete frequency node

    @param [in] del Node which we want to delete
*/
void RemoveFreq(struct freq_node* del);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Delete first lfu node with frequency 1

    @param [in] head Pointer to List
*/
void RemoveLfu(struct freq_node* head);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief When we already have the resulting item in the list, we need to replaceit. 
    If the element with current frequency + 1 doesn`t exist it will
    be created (with function create_freq).

    @param [in] cur_lfu Lfu node which we want to replace
*/
void ReplaceLfu(struct lfu_node* cur_lfu);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Initialization of head of list
*/
struct freq_node* CreateHead();
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Function which free's list
*/
void DeleteList(struct freq_node* head);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Function which print List to filestream

    @param [in] head Pointer to head of list
    @param [in] f Filestream pointer where we want to print list
*/
void ListPrint(struct freq_node* head, FILE* f);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//Test functions
void TestCreateHead();
void TestCreateFreq();
void TestCreateLfu();
void TestRemoveFreq();
void TestRemoveLfu();
void TestReplaceLfu();
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Node which contains pages with data
*/
struct lfu_node
{
    struct request_t data_t;
    struct lfu_node * next;
    struct lfu_node * prev;

    struct freq_node* parent;

};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Node which contains frequency
*/
struct freq_node
{
    int freq_t;
    struct freq_node* next;
    struct freq_node* prev;

    struct lfu_node * child;

};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
// Hash-table part
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_cell;
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_map* InitHashMap (int cache_size);
struct hash_cell* SearchData (struct hash_cell* cell, DATA* request);
struct hash_cell* InsertHashMap (struct hash_map* Hash_Map, DATA* request);
struct hash_cell* SearchMap (struct hash_map* Hash_Map, DATA* request);
int HashofData (DATA* request, int cache_size);
int HashofChar (char* string, int len, int cache_size);
int DelElem (struct hash_map* Hash_Map, DATA* request);
int FreeHashMap (struct hash_map* Hash_Map);
int PrintHashMap (struct hash_map* Hash_Map, FILE* f);
int HashofInt (int number, int cache_size);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct hash_cell
{
    struct hash_cell* next;
    struct hash_cell* prev;
    struct lfu_node * item;

};

struct hash_map
{
    struct hash_cell** cells;
    int               size;

};
//LFU - part
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Struct of LFU - cache
*/
typedef struct lfu_c LFU;

struct lfu_c
{
    struct hash_map* HashTable;
    struct freq_node* List;

    int cache_size;
    int cache_fullnes;
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Function which get stream-variable and read page with data from it

    @param [in] f Filestream which you want to take a page from

    @return Page of data (type DATA)
*/
DATA GetPage (FILE* f);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Function which print page with data to file with name "source"

    @param [in] page Pointer to page with data
    @param [in] source String with name of file

    @note If source is "stdout", data will be printed to console
*/
void PrintPage (DATA* page, char* source);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Constructor of LFU - cache

    @param [in] cache_size Size of cache

    @return Pointer to initialized cache
*/
LFU* LfuConstruct (int cache_size);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Func which insert new page to cache

    @param [in] cache Pointer to cache where we want to insert
    @param [in] request Page of data which we want to insert

    @return 1, if there is this page in cache< 0 if it isn't
*/
int InsertLFU (LFU* cache, DATA* request);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Destructor of LFU-cache

    @param [in] cache Pointer to LFU-cache
*/
void FreeLFU (LFU* cache);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Func which print LFU-cache to file with name "source"

    @param [in] cache LFU-cache which we want to print
    @param [in] source Name of file where we want to print

    @note If source is "stdout" data will be printed to console
*/
void LFUDump (LFU* cache, char* source);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Macros which call GetPage func with f = stdin
*/
#define CGetPage() GetPage(stdin);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief Macros which call PrintPage func with source = "stdout"
*/
#define CPrintPage(page) PrintPage(page, "stdout")
