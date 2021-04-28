#pragma once
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct lfu_node;
struct freq_node;
struct hash_cell;
struct hash_map Init_Hash_Map ();
void Free_Hash_Map (struct hash_map Hash_Map);
struct lfu_node* Lfu_Node_Constuct (struct lfu_node* node);
struct hash_cell* Search_Data (struct hash_cell* cell, int data);
void Insert_Hash_Map (struct hash_map* Hash_Map, int data);
int Hash_of_Data (int data);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct lfu_node {
  
    int data_t;
    struct lfu_node * next;
    struct lfu_node * prev;
  
    struct freq_node* parent;

};
struct freq_node {
  
    int freq_t;
    struct freq_node* next;
    struct freq_node* prev;

    struct lfu_node * child;
   
};
struct hash_cell {

    struct hash_cell* next;
    struct lfu_node * item;

};
struct hash_map {

    struct hash_cell* cells;
    int               size;

};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
enum Const_Values {

    cache_size = 2048

};