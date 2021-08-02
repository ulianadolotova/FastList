#include "List.h"

int main ()
{
    smart_list* list_ptr = List_Construct (10);

    for (size_t i = 1; i < 5; i++)
        List_Insert_Head (list_ptr, i);

    List_Insert_Place_After (list_ptr, 77, 0);
    List_Extract_Head (list_ptr);
    List_Insert_Tail (list_ptr, 99);

    list_ptr = Very_Long_Sort_To_Put_Harmony_Between_Logical_And_Physical_Indexes (list_ptr);

    for (size_t i = 0; i < 11; i++)
    {
        printf("\n\n\nlist_ptr->capacity is %d", list_ptr->capacity);
        printf("\nlist_ptr->size_list is %d", list_ptr->size_list);
        printf("\nlist_ptr->index_head is %d", list_ptr->index_head);
        printf("\nlist_ptr->index_tail is %d", list_ptr->index_tail);
        printf("\nlist_ptr->index_free is %d", list_ptr->index_free);

        printf ("\nlist_ptr-arr_nodes[%d].value is %lg", i, list_ptr->arr_nodes[i].value);
        printf ("\nlist_ptr-arr_nodes[%d].index_next is %d", i, list_ptr->arr_nodes[i].index_next);
        printf ("\nlist_ptr-arr_nodes[%d].index_prev is %d\n\n", i, list_ptr->arr_nodes[i].index_prev);
    }

    /*for (size_t i = 1; i < 2; i++)
        printf("\n\n%lg",List_Extract_Head (list_ptr));

    for (size_t i = 0; i < 11; i++)
    {
        printf("\n\n\nlist_ptr->capacity is %d", list_ptr->capacity);
        printf("\nlist_ptr->size_list is %d", list_ptr->size_list);
        printf("\nlist_ptr->index_head is %d", list_ptr->index_head);
        printf("\nlist_ptr->index_tail is %d", list_ptr->index_tail);
        printf("\nlist_ptr->index_free is %d", list_ptr->index_free);

        printf ("\nlist_ptr-arr_nodes[%d].value is %lg", i, list_ptr->arr_nodes[i].value);
        printf ("\nlist_ptr-arr_nodes[%d].index_next is %d", i, list_ptr->arr_nodes[i].index_next);
        printf ("\nlist_ptr-arr_nodes[%d].index_prev is %d\n\n", i, list_ptr->arr_nodes[i].index_prev);
    }  */


    // ("\n\nGet_Index (list_ptr, 4) is %d\n\n", Get_Index (list_ptr, 4));
    Dump_Graph_Logical  (list_ptr);
    Dump_Graph_Physical (list_ptr);

    printf ("\n%d\n",Dump_Text (list_ptr));

    return 0;
}




smart_list* List_Construct (size_t capacity)
{
    assert (capacity > 0);

    capacity += 1;

    smart_list* list_ptr = (smart_list*) calloc (1, sizeof (smart_list));
    assert (list_ptr);

    list_ptr->arr_nodes = (node_list*) calloc (capacity, sizeof (node_list));
    assert (list_ptr->arr_nodes);

    list_ptr->capacity   = capacity;
    list_ptr->size_list  = 0;
    list_ptr->index_head = 0;
    list_ptr->index_tail = 0;
    list_ptr->index_free = 1;

    size_t i = 0;

    for (i = 1; i < list_ptr->capacity - 1; i++)
    {
        list_ptr->arr_nodes[i].index_next = i + 1;
        list_ptr->arr_nodes[i].index_prev = i - 1;
        list_ptr->arr_nodes[i].value      = NAN;
    }

    list_ptr->arr_nodes[0].value      = NAN;
    list_ptr->arr_nodes[i].value      = NAN;
    list_ptr->arr_nodes[i].index_next = 0;
    list_ptr->arr_nodes[i].index_prev = i - 1;

    LIST_OK(list_ptr)

    return list_ptr;
}




void List_Destruct (smart_list* list_ptr)
{
    LIST_OK(list_ptr)

    list_ptr->capacity   = 0;
    list_ptr->size_list  = 0;
    list_ptr->index_head = 0;
    list_ptr->index_tail = 0;
    list_ptr->index_free = 0;

    free (list_ptr->arr_nodes);
    free (list_ptr);
}




void List_Insert_Head (smart_list* list_ptr, elem_t value)
{
    LIST_OK(list_ptr)
    List_Insert_Place_After (list_ptr, value, 0);
    LIST_OK(list_ptr)
}




void List_Insert_Tail (smart_list* list_ptr, elem_t value)
{
    LIST_OK(list_ptr)

    List_Insert_Place_After (list_ptr, value, list_ptr->index_tail);

    LIST_OK(list_ptr)
}




elem_t List_Extract_Place (smart_list* list_ptr, size_t place)
{
    LIST_OK(list_ptr)

    assert (list_ptr->size_list > 0);

    elem_t saved_value = list_ptr->arr_nodes[place].value;

    list_ptr->arr_nodes[list_ptr->arr_nodes[place].index_next].index_prev = list_ptr->arr_nodes[place].index_prev;

    if (place != list_ptr->index_head)
        list_ptr->arr_nodes[list_ptr->arr_nodes[place].index_prev].index_next = list_ptr->arr_nodes[place].index_next;
    else
        list_ptr->index_head = list_ptr->arr_nodes[place].index_next;

    list_ptr->arr_nodes[place].index_prev = 0;
    list_ptr->arr_nodes[place].index_next = list_ptr->index_free;
    list_ptr->arr_nodes[place].value      = NAN;

    list_ptr->arr_nodes[list_ptr->index_free].index_prev = place;

    list_ptr->index_free = place;

    list_ptr->size_list--;

    LIST_OK(list_ptr)

    return saved_value;
}




elem_t List_Extract_Head (smart_list* list_ptr)
{
    LIST_OK(list_ptr)

    return List_Extract_Place (list_ptr, list_ptr->index_head);
}




elem_t List_Extract_Tail (smart_list* list_ptr)
{
    LIST_OK(list_ptr)

    return List_Extract_Place (list_ptr, list_ptr->index_tail);
}




void List_Insert_Place_After (smart_list* list_ptr, elem_t value, size_t place)
{
    LIST_OK(list_ptr)

    size_t saved_free = list_ptr->index_free;

    list_ptr->index_free = list_ptr->arr_nodes[saved_free].index_next;
    list_ptr->arr_nodes[list_ptr->index_free].index_prev = 0;

    list_ptr->arr_nodes[saved_free].index_prev = place;
    list_ptr->arr_nodes[saved_free].value      = value;

    if (place == 0)
    {
        list_ptr->arr_nodes[saved_free].index_next = list_ptr->index_head;
        list_ptr->index_head = saved_free;
    }

    else
    {
        list_ptr->arr_nodes[saved_free].index_next = list_ptr->arr_nodes[place].index_next;
    }

    if (place != 0)
        list_ptr->arr_nodes[list_ptr->arr_nodes[saved_free].index_prev].index_next = saved_free;

    if (list_ptr->arr_nodes[saved_free].index_next != 0)
        list_ptr->arr_nodes[list_ptr->arr_nodes[saved_free].index_next].index_prev = saved_free;

    list_ptr->size_list++;

    LIST_OK(list_ptr)
}




void List_Insert_Place_Before (smart_list* list_ptr, elem_t value, size_t place)
{
    LIST_OK(list_ptr)
    assert (place > 0);

    List_Insert_Place_After (list_ptr, value, place - 1);

    LIST_OK(list_ptr)
}




size_t Get_Index (smart_list* list_ptr, size_t logical_place)
{
    LIST_OK(list_ptr)

    assert (logical_place <= list_ptr->size_list);
    assert (logical_place > 0);

    size_t count = 1;
    size_t i = list_ptr->index_head;

    while (count != list_ptr->size_list)
    {
        if (count == logical_place)
            break;
        else
            count++;

        i = list_ptr->arr_nodes[i].index_next;
    }

    LIST_OK(list_ptr)

    return i;
}




smart_list* Very_Long_Sort_To_Put_Harmony_Between_Logical_And_Physical_Indexes (smart_list* list_ptr)
{
    LIST_OK(list_ptr)

    smart_list* new_ptr = List_Construct (list_ptr->capacity - 1);
    assert (new_ptr);

    size_t ptr = list_ptr->index_head;
    size_t i   = 1;
    for (; i < list_ptr->size_list; i++)
    {
        new_ptr->arr_nodes[i].index_prev  = i - 1;
        new_ptr->arr_nodes[i].value = list_ptr->arr_nodes[ptr].value;

        if (i != list_ptr->size_list - 1)
            new_ptr->arr_nodes[i].index_next  = i + 1;
        else
            new_ptr->arr_nodes[i].index_next  = 0;

        ptr = list_ptr->arr_nodes[ptr].index_next;

    }

    new_ptr->index_free = i;
    new_ptr->size_list = list_ptr->size_list;
    if (new_ptr->size_list > 0)
        new_ptr->index_head = 1;

    List_Destruct (list_ptr);

    LIST_OK(new_ptr)

    return new_ptr;
}
