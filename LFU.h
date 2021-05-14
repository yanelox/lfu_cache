#pragma once
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#define NUM 1000
//---------------------------------------------------------------------
//---------------------------------------------------------------------
typedef struct request_t DATA;
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct request_t      //change it like you want
{
    int               data;
    float             d;
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
struct freq_node* create_freq(int freq_dat, struct freq_node* prev_fr);
struct lfu_node* create_lfu(DATA* lfu_dat, struct freq_node* head);
void remove_freq(struct freq_node* del);
void remove_lfu(struct freq_node* head);
void replace_lfu(struct lfu_node* cur_lfu);
struct freq_node* create_head();
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
struct hash_map* Init_Hash_Map ();
struct lfu_node* Lfu_Node_Constuct ();
struct hash_cell* Search_Data (struct hash_cell* cell, DATA* request);
int Insert_Hash_Map (struct hash_map* Hash_Map, DATA* request);
int Hash_of_Data (DATA* request);
int Hash_of_Char (char* string, int len);
int Free_Hash_Map (struct hash_map* Hash_Map);
//int Test_Hash_Map (struct hash_map* Hash_Map);
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
    struct hash_cell* cells;
    int               size;

};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
enum Const_Values
{
    cache_size = 2048

};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//LFU - part
//---------------------------------------------------------------------
//---------------------------------------------------------------------
DATA* GetPage (char* source);
void PrintPage (DATA* page, char* source);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#define CGetPage() GetPage("stdin");
#define CPrintPage(page) PrintPage(page, "stdout")
