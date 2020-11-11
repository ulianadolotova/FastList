#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

typedef double elem_t;
typedef int    error_t;

#define LIST_OK(list_ptr)   if (List_OK(list_ptr) != OK) \
                            {                            \
                                Dump_All(list_ptr);      \
                                assert(!"OK");           \
                            }                            \

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


const size_t MAX_ERROR_NAME = 30;


enum errors
{
    OK                       = 0,

    NULL_LIST_PTR            = 1,

    NULL_ARR_NODES           = 2,

    CAPACITY_LESS_SIZE       = 3,

    ELEM_IS_NAN              = 4,

    NO_SUCH_INDEX            = 5,

    ERROR_LOG_FILE           = 6,

    ZERO_NODE_IS_NOT_NAN     = 7,

    ZERO_NODE_PREV_INCORRECT = 8,

    ZERO_NODE_NEXT_INCORRECT = 9,

    HEAD_NODE_INCORRECT      = 10,

    TAIL_NODE_INCORRECT      = 11,

    FREE_NODE_INCORRECT      = 12,

    FREE_IS_NOT_NAN          = 13

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
size_t      Get_Index                (smart_list* list_ptr, size_t logical_place);

smart_list* Very_Long_Sort_To_Put_Harmony_Between_Logical_And_Physical_Indexes (smart_list* list_ptr);

error_t Dump_Graph_Physical (smart_list* list_ptr);
error_t Dump_Graph_Logical  (smart_list* list_ptr);
error_t List_OK             (smart_list* list_ptr);
error_t Dump_Text           (smart_list* list_ptr);
void    Dump_All            (smart_list* list_ptr);
