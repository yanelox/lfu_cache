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