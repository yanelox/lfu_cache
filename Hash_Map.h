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
struct request_t;
struct lfu_node;
struct freq_node;
struct hash_cell;
struct hash_map* Init_Hash_Map ();
int Free_Hash_Map (struct hash_map* Hash_Map);
struct lfu_node* Lfu_Node_Constuct ();
struct hash_cell* Search_Data (struct hash_cell* cell, struct request_t* request);
int Insert_Hash_Map (struct hash_map* Hash_Map, struct request_t* request);
int Hash_of_Data (struct request_t* request);
int Hash_of_Char (char* string, int len);
//int Test_Hash_Map (struct hash_map* Hash_Map);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct request_t
{
    int               data;
    char c;
    float d;
};

struct lfu_node
{
    struct request_t* data_t;
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
