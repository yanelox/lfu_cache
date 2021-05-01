#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "Hash_Map.h"

//---------------------------------------------------------------------

struct freq_node* create_freq(int freq_dat, struct freq_node* prev_fr)                                 //prev_fr != NULL!! That function doesn`t create head!
{
    struct freq_node* res;

    assert(prev_fr != NULL);

    res = (struct freq_node*)calloc(1, sizeof(struct freq_node));
    res->freq_t = freq_dat;
    res->prev = prev_fr;
    res->next = NULL;

    if(prev_fr->next != NULL)
    {
        prev_fr->next->prev = res;
        res->next = prev_fr->next;
    }

    prev_fr->next = res;

    return res;
}

//---------------------------------------------------------------------

struct lfu_node* create_lfu(struct request_t* lfu_dat, struct freq_node* parent_lfu, struct lfu_node* prev_lfu)       //prev_lfu may be NULL
{
    struct lfu_node* res;

    assert(parent_lfu != NULL);

    res = (struct lfu_node*)calloc(1, sizeof(struct lfu_node));
    res->data_t = lfu_dat;
    res->parent = parent_lfu;
    res->prev = prev_lfu;

    if(prev_lfu != NULL)
        prev_lfu->next = res;

    return res;
}

//---------------------------------------------------------------------

void remove_freq(struct freq_node* del)                                                                 //del->prev != NULL and del->next != NULL
{
    assert(del->prev != NULL);
    assert(del->next != NULL);

    del->next->prev = del->prev;
    del->prev->next = del->next;

    free(del);

    return;
}

//---------------------------------------------------------------------

void remove_lfu(struct freq_node* head)
{
    struct lfu_node* res;
    struct freq_node* cur_fr;

    assert(head->next != NULL);

    cur_fr = head->next;
    res = cur_fr->child;

    if(res->next != NULL)
    {
        res->next->prev = NULL;
        cur_fr->child = res->next;
    }

    else
        remove_freq(cur_fr);

    free(res);

    return;
}

//---------------------------------------------------------------------

void replace_lfu(struct lfu_node* cur_lfu)
{
    int data = cur_lfu->parent->freq_t;
    struct freq_node* cur_fr = cur_lfu->parent;
    struct lfu_node* last = NULL;
    struct freq_node* new_fr = NULL;

    if(cur_lfu->prev != NULL)

        if(cur_lfu->next != NULL)
        {
            cur_lfu->next->prev = cur_lfu->prev;
            cur_lfu->prev->next = cur_lfu->next;
        }

        else
            cur_lfu->prev->next = NULL;

    else

        if(cur_lfu->next != NULL)
        {
            cur_lfu->parent->child = cur_lfu->next;
            cur_lfu->next->prev = NULL;
        }

        else
            remove_freq(cur_lfu->parent);

    cur_lfu->prev = NULL;
    cur_lfu->next = NULL;


    if(cur_fr->next != NULL && cur_fr->next->freq_t == data + 1)
    {
        cur_fr = cur_fr->next;

        cur_lfu->parent = cur_fr;
        last = cur_fr->child;

        while(last->next != NULL)
            last = last->next;

        last->next = cur_lfu;
        cur_lfu->prev = last;
    }

    else
    {
        new_fr = create_freq(data + 1, cur_fr);
        new_fr->child = cur_lfu;
        cur_lfu->parent = new_fr;
    }

    return;
}

//---------------------------------------------------------------------
