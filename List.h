#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

typedef double elem_t;


struct node_list
{
    elem_t value;
    size_t index_prev;
    size_t index_next;
};


struct smart_list
{
    node_list* arr_nodes;
    size_t     capacity;
    size_t     size_list;
    size_t     index_head;
    size_t     index_tail;
    size_t     index_free;
};


smart_list* List_Construct           (size_t capacity);
void        List_Destruct            (smart_list* list_ptr);
void        List_Insert_Place_After  (smart_list* list_ptr, elem_t value, size_t place);
void        List_Insert_Place_Before (smart_list* list_ptr, elem_t value, size_t place);
void        List_Insert_Head         (smart_list* list_ptr, elem_t value);
void        List_Insert_Tail         (smart_list* list_ptr, elem_t value);
elem_t      List_Extract_Place       (smart_list* list_ptr, size_t place);
elem_t      List_Extract_Head        (smart_list* list_ptr);
elem_t      List_Extract_Tail        (smart_list* list_ptr);


void Dump_Graph_Physical (smart_list* list_ptr);
void Dump_Graph_Logical  (smart_list* list_ptr);
