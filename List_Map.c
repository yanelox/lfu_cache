#include "LFU.h"

//---------------------------------------------------------------------
//Creates an element in the place the user wants. Function need data(frequency)
//and previous item (place where we should create)
//---------------------------------------------------------------------
struct freq_node* create_freq(int freq_dat, struct freq_node* prev_fr)                      //prev_fr != NULL!! That function doesn`t create head!
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
// Creates last lfu_node at frequency 1. If frequency 1 is not exist, it will
// be created (with function create_freq).
//---------------------------------------------------------------------
struct lfu_node* create_lfu(DATA* lfu_dat, struct freq_node* head)
{
    struct lfu_node* res;
    struct lfu_node* cur_lfu = NULL;
    struct freq_node* cur_fr;

    assert(head != NULL);

    res = (struct lfu_node*)calloc(1, sizeof(struct lfu_node));
    res->data_t = lfu_dat;

    if(head->next != NULL && head->next->freq_t == 1)
    {
        cur_fr = head->next;
        cur_lfu = cur_fr->child;

        while(cur_lfu->next != NULL)
            cur_lfu = cur_lfu->next;

        res->parent = cur_fr;
        res->prev = cur_lfu;
        cur_lfu->next = res;
        res->next = NULL;
    }

    else
    {
        cur_fr = create_freq(1, head);
        res->parent = cur_fr;
        cur_fr->child = res;
        res->next = NULL;
        res->prev = NULL;
    }

    return res;
}
//---------------------------------------------------------------------
//delete freq_node
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
//delete lfu_node
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
//When we already have the resulting item in the list, we need to replace
//it. If the element with current frequency + 1 doesn`t exist it will
//be created (with function create_freq).
//---------------------------------------------------------------------
void replace_lfu(struct lfu_node* cur_lfu)
{
    int data = cur_lfu->parent->freq_t;
    struct freq_node* cur_fr = cur_lfu->parent;
    struct lfu_node* last = NULL;
    struct freq_node* new_fr = NULL;
    int delet = 0;

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
            delet = 1;

    cur_lfu->prev = NULL;
    cur_lfu->next = NULL;


    if(cur_fr->next != NULL && cur_fr->next->freq_t == data + 1)
    {
        cur_lfu->parent = cur_fr->next;
        last = cur_fr->next->child;

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

    if(delet == 1)
        remove_freq(cur_fr);

    return;
}
//---------------------------------------------------------------------
struct freq_node* create_head()
{
    struct freq_node* head;

    head = (struct freq_node*)calloc(1, sizeof(struct freq_node));
    head->next = NULL;
    head->prev = NULL;
    head->child = NULL;

    return head;
}
//---------------------------------------------------------------------
