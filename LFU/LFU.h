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
struct freq_node* CreateFreq(int freq_dat, struct freq_node* prev_fr);
struct lfu_node* CreateLfu(DATA lfu_dat, struct freq_node* head);
void RemoveFreq(struct freq_node* del);
void RemoveLfu(struct freq_node* head);
void ReplaceLfu(struct lfu_node* cur_lfu);
struct freq_node* CreateHead();
void DeleteList(struct freq_node* head);
void ListPrint(struct freq_node* head, FILE* f);
void TestCreateHead();
void TestCreateFreq();
void TestCreateLfu();
void TestRemoveFreq();
void TestRemoveLfu();
void TestReplaceLfu();
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct lfu_node
{
    struct request_t data_t;
    struct lfu_node * next;
    struct lfu_node * prev;

    struct freq_node* parent;

};

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
/*!
    \brief This function is constructor of hash table; it initializes Hash Map,
           calculates the size of hash using the formula {Size = cache_size / 10 + 1},
           initialzes array of pointers to cells and cells
    @param [in] cache_size The size of cache 
    @return Pointer to allocated memory to Hash Map 
*/
struct hash_map* InitHashMap (int cache_size);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief This function searches data in list of collisions
    @param [in] cell Element of array of pointers to cells in Hash Map
    @param [in] request Request 
    @return Pointer to cell and NULL pointer if data hasn't been found 
*/
struct hash_cell* SearchData (struct hash_cell* cell, DATA* request);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief This function finds an avaliable place to adding new data
           If this data already exists here, it does nothing 
    @param [in] Hash_Map pointer to Hash Map 
    @param [in] request pointer to request 
    @return The pointer on an avaliable cell in Hash Map
*/
struct hash_cell* InsertHashMap (struct hash_map* Hash_Map, DATA* request);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief This function searches data in Hash Map
    @param [in] Hash_Map pointer to Hash Map 
    @param [in] request pointer to request 
    @return Pointer to cell and NULL pointer if data hasn't been found
*/
struct hash_cell* SearchMap (struct hash_map* Hash_Map, DATA* request);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief This function transforms struct to string for calculating hash later
    @param [in] request pointer to request 
    @param [in] hash_size The size of Hash
    @return Key of Hash Table
*/
int HashofData (DATA* request, int hash_size);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief This function calculates hash of string
    @param [in] string String 
    @param [in] len The length of string
    @param [in] hash_size The size of Hash
    @return Hash of string
*/
int HashofChar (char* string, int len, int hash_size);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief This function calculates hash of integer number
    @param [in] number Integer number 
    @param [in] hash_size The size of Hash
    @return Hash of integer number
*/
int HashofInt (int number, int hash_size);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief This function deletes cell with node with data from Hash Map and do nothing
           if data isn't here
    @param [in] Hash_map Pointer to Hash Map 
    @param [in] request Request
    @return Integer zero
*/
int DelElem (struct hash_map* Hash_Map, DATA* request);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief This function clear memory allocated for Hash_Map, array of pointers
           to cells and cells
    @param [in] Hash_map Pointer to Hash Map 
    @return Integer zero
*/
int FreeHashMap (struct hash_map* Hash_Map);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief This function print Hash Map
    @param [in] Hash_map Pointer to Hash Map 
    @param [in] f Pointer to file stream
    @return Integer zero
*/
int PrintHashMap (struct hash_map* Hash_Map, FILE* f);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief The cell of hash table
*/
struct hash_cell
{
    struct hash_cell* next;
    struct hash_cell* prev;
    struct lfu_node * item;

};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*!
    \brief The struct of Hash Map
*/
struct hash_map
{
    struct hash_cell** cells;
    int               size;

};
//LFU - part
//---------------------------------------------------------------------
//---------------------------------------------------------------------
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
DATA GetPage (FILE* f);
void PrintPage (DATA* page, char* source);
LFU* LfuConstruct (int cache_size);
int InsertLFU (LFU* cache, DATA* request);
void FreeLFU (LFU* cache);
void LFUDump (LFU* cache, char* source);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#define CGetPage() GetPage(stdin);
#define CPrintPage(page) PrintPage(page, "stdout")
