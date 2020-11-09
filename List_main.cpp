#include "List.h"

int main ()
{
    smart_list* list_ptr = List_Construct (10);

    for (size_t i = 1; i < 5; i++)
        List_Insert_Head (list_ptr, i);

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

    List_Insert_Place_After (list_ptr, 77, 3);

    Dump_Graph_Logical  (list_ptr);
    Dump_Graph_Physical (list_ptr);


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
    list_ptr->index_head = 1;
    list_ptr->index_tail = 1;
    list_ptr->index_free = 1;

    size_t i = 0;

    for (i = 1; i < list_ptr->capacity - 1; i++)
    {
        list_ptr->arr_nodes[i].index_next = i + 1;
        list_ptr->arr_nodes[i].index_prev = i - 1;
        list_ptr->arr_nodes[i].value      = NAN;
    }

    list_ptr->arr_nodes[i].value      = NAN;
    list_ptr->arr_nodes[i].index_next = 0;
    list_ptr->arr_nodes[i].index_prev = i - 1;

    return list_ptr;
}




void List_Destruct (smart_list* list_ptr)
{
    assert (list_ptr);
    assert (list_ptr->arr_nodes);

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
    assert (list_ptr);
    assert (list_ptr->arr_nodes);

    size_t saved_index_head = list_ptr->index_head;
    size_t saved_next_free  = list_ptr->arr_nodes[list_ptr->index_free].index_next;

    list_ptr->index_head   = list_ptr->index_free;
    list_ptr->arr_nodes[saved_index_head].index_prev = list_ptr->index_head;

    list_ptr->arr_nodes[list_ptr->index_head].value      = value;
    list_ptr->arr_nodes[list_ptr->index_head].index_prev = 0;
    list_ptr->arr_nodes[list_ptr->index_head].index_next = saved_index_head;

    if (list_ptr->size_list == 0)
        list_ptr->arr_nodes[list_ptr->index_head].index_next = 0;

    list_ptr->index_free = saved_next_free;
    list_ptr->arr_nodes[list_ptr->index_free].index_prev = 0;

    list_ptr->size_list++;
}




elem_t List_Extract_Head (smart_list* list_ptr)
{
    assert (list_ptr);
    assert (list_ptr->arr_nodes);

    assert (list_ptr->size_list > 0);

    size_t saved_index_head = list_ptr->index_head;
    elem_t saved_value      = list_ptr->arr_nodes[list_ptr->index_head].value;

    if (list_ptr->size_list > 1)
    {
        list_ptr->index_head = list_ptr->arr_nodes[saved_index_head].index_next;
        list_ptr->arr_nodes[list_ptr->index_head].index_prev = 0;
    }

    list_ptr->arr_nodes[saved_index_head].index_prev  = 0;
    list_ptr->arr_nodes[saved_index_head].index_next  = list_ptr->index_free;
    list_ptr->arr_nodes[saved_index_head].value       = 0;

    list_ptr->arr_nodes[list_ptr->index_free].index_prev = saved_index_head;

    list_ptr->index_free = saved_index_head;

    list_ptr->size_list--;

    return saved_value;
}




void List_Insert_Place_After (smart_list* list_ptr, elem_t value, size_t place)
{
    assert (list_ptr);
    assert (list_ptr->arr_nodes);

    size_t saved_free = list_ptr->index_free;

    list_ptr->index_free = list_ptr->arr_nodes[saved_free].index_next;
    list_ptr->arr_nodes[list_ptr->index_free].index_prev = 0;


}
