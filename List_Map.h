#pragma once
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Hash_Map.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct lfu_node;
struct freq_node;
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct freq_node* create_freq(int freq_dat, struct freq_node* prev_fr);
struct lfu_node* create_lfu(DATA* lfu_dat, struct freq_node* head)
void remove_freq(struct freq_node* del);
void remove_lfu(struct freq_node* head);
void replace_lfu(struct lfu_node* cur_lfu);
struct freq_node* create_head();
//---------------------------------------------------------------------
//---------------------------------------------------------------------
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
//---------------------------------------------------------------------
//---------------------------------------------------------------------
