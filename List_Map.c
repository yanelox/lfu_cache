#include "LFU.h"

//---------------------------------------------------------------------
//Creates an element in the place the user wants. Function need data(frequency)
//and previous item (place where we should create)
//---------------------------------------------------------------------
struct freq_node* CreateFreq(int freq_dat, struct freq_node* prev_fr)                      //prev_fr != NULL!! That function doesn`t create head!
{
    struct freq_node* res;

    assert(prev_fr != NULL);

    res = (struct freq_node*)calloc(1, sizeof(struct freq_node));
    res->freq_t = freq_dat;
    res->prev = prev_fr;
    res->next = NULL;
    res->child = NULL;

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
struct lfu_node* CreateLfu(DATA lfu_dat, struct freq_node* head)
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
        cur_fr = CreateFreq(1, head);
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
void RemoveFreq(struct freq_node* del)                                                                 //del->prev != NULL and del->next != NULL
{
    assert(del->prev != NULL);
    assert(del->next != NULL); //

    del->next->prev = del->prev;
    del->prev->next = del->next;

    free(del);

    return;
}
//---------------------------------------------------------------------
//delete lfu_node
//---------------------------------------------------------------------
void RemoveLfu(struct freq_node* head)
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
        RemoveFreq(cur_fr);

    free(res);

    return;
}
//---------------------------------------------------------------------
//When we already have the resulting item in the list, we need to replace
//it. If the element with current frequency + 1 doesn`t exist it will
//be created (with function create_freq).
//---------------------------------------------------------------------
void ReplaceLfu(struct lfu_node* cur_lfu)
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
        new_fr = CreateFreq(data + 1, cur_fr);
        new_fr->child = cur_lfu;
        cur_lfu->parent = new_fr;
    }

    if(delet == 1)
        RemoveFreq(cur_fr);

    return;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct freq_node* CreateHead()
{
    struct freq_node* head;

    head = (struct freq_node*)calloc(1, sizeof(struct freq_node));
    head->next = NULL;
    head->prev = NULL;
    head->child = NULL;

    return head;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void DeleteList(struct freq_node* head)
{
    struct freq_node* cur_f = head;
    struct freq_node* ftmp;
    struct lfu_node* cur_l;
    struct lfu_node* ltmp;

    while (cur_f)
    {
        if (cur_f->child)
        {
            cur_l = cur_f->child;

            while (cur_l)
            {
                ltmp = cur_l;
                cur_l = cur_l->next;
                free (ltmp);
            }
        }

        ftmp = cur_f;
        cur_f = cur_f->next;
        free (ftmp);
    }

    return;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void ListPrint(struct freq_node* head)
{
    struct freq_node* cur_f = head;
    struct lfu_node* cur_l;

    if(cur_f->next == NULL)
        printf("The list is empty -_-");

    while(cur_f->next != NULL)
    {
        cur_f = cur_f->next;
        printf("freq %d: ", cur_f->freq_t);

        if(cur_f->child = NULL)
            printf("ERRO_OR there is no elements");
        else
        {
            cur_l = cur_f->child;

            while(cur_l->next != NULL)
            {
                printf("%d ", cur_l->data_t.data);
                cur_l = cur_l->next;
            }

            printf("%d;\n", cur_l->data_t.data);
        }
    }
    return;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void TestCreateHead()
{
    struct freq_node* head;
    head = CreateHead();

    assert(head != NULL);
    assert(head->next == NULL);
    assert(head->prev == NULL);
    assert(head->child == NULL);
    free(head);

    return;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void TestCreateFreq()
{
    struct freq_node* head;
    struct freq_node* first;
    struct freq_node* second;
    struct freq_node* third;

    head = CreateHead();

    first = CreateFreq(1, head);
    third = CreateFreq(3, first);

    assert(first != NULL);
    assert(third != NULL);

    assert(first->prev == head);
    assert(third->prev == first);

    assert(first->next == third);
    assert(head->next == first);
    assert(third->next == NULL);

    assert(first->freq_t == 1);
    assert(third->freq_t == 3);

    assert(third->child == NULL);
    assert(first->child == NULL);

    second = CreateFreq(2, first);

    assert(second != NULL);

    assert(first->next == second);
    assert(second->next == third);

    assert(second->freq_t == 2);
    assert(second->child == NULL);

    assert(second->prev == first);
    assert(third->prev == second);

    free(first);
    free(second);
    free(third);
    free(head);

    return;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void TestCreateLfu()
{
    struct lfu_node* lf1;
    struct lfu_node* lf2;
    DATA dat1;
    DATA dat2;
    struct freq_node* head;
    struct freq_node* par;

    head = CreateHead();

    lf1 = CreateLfu(dat1, head);
    assert(lf1->next == NULL);

    lf2 = CreateLfu(dat2, head);
    par = lf1->parent;

    assert(lf1 != NULL);
    assert(lf2 != NULL);

    assert(par == lf2->parent);
    assert(par->child == lf1);
    assert(par->freq_t == 1);

    assert(lf1->next == lf2);
    assert(lf2->prev == lf1);
    assert(lf1->prev == NULL);

    free(par);
    free(lf1);
    free(lf2);

    return;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void TestRemoveFreq()
{
    struct freq_node* head;
    struct freq_node* first;
    struct freq_node* second;

    head = CreateHead();
    first = CreateFreq(1, head);
    second = CreateFreq(2, first);

    RemoveFreq(first);

    assert(second->prev == head);
    assert(head->next == second);

    free(second);
    free(head);

    return;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void TestRemoveLfu()
{
    struct lfu_node* lf1;
    struct lfu_node* lf2;
    DATA dat1, dat2;
    struct freq_node* head;
    struct freq_node* par;

    head = CreateHead();

    lf1 = CreateLfu(dat1, head);
    par = lf1->parent;
    lf2 = CreateLfu(dat2, head);
    RemoveLfu(head);

    assert(head != NULL);
    assert(par != NULL);
    assert(lf2 != NULL);
    assert(par->child == lf2);
    assert(lf2->next == NULL);
    assert(lf2->prev == NULL);

    free(lf2);
    free(par);
    free(head);

    return;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void TestReplaceLfu()
{
    struct lfu_node* lf1;
    struct lfu_node* lf2;
    struct lfu_node* lf3;
    DATA dat1, dat2, dat3;
    struct freq_node* head;
    struct freq_node* par;
    struct freq_node* par2;

    head = CreateHead();
    lf1 = CreateLfu(dat1, head);
    par = lf1->parent;
    ReplaceLfu(lf1);

    assert(lf1->parent != NULL);

    par = lf1->parent;
    assert(par->freq_t == 2);
    assert(par->child == lf1);
    assert(head->next == par);
    assert(par->prev == head);

    lf2 = CreateLfu(dat2, head);
    lf3 = CreateLfu(dat3, head);
    ReplaceLfu(lf2);
    par2 = head->next;

    assert(par2->child == lf3);
    assert(par->child == lf1);
    assert(lf1->next == lf2);
    assert(lf2->prev == lf1);
    assert(lf2->next == NULL);
    assert(lf3->prev == NULL);
    assert(lf2->parent == par);

    free(lf2);
    free(lf1);
    free(lf3);
    free(head);
    free(par);
    free(par2);

    return;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------


