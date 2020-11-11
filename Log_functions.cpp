#include "List.h"

error_t Dump_Graph_Physical (smart_list* list_ptr)
{
    assert (list_ptr);
    assert (list_ptr->arr_nodes);

    FILE* file_graph = fopen ("DumpGraph_list_physical.txt", "w");

    fprintf (file_graph, "digraph G {\n");
    fprintf (file_graph, "node [shape = \"record\", style = \"filled\", color = \"#A80800\", fillcolor = \"#C0FFEE\"];\n");

    fprintf (file_graph, "\"%p\" [label = \"{BEGIN}\"];\n", list_ptr->arr_nodes);
    fprintf (file_graph, "\"%p\"->\"%p\"\n", list_ptr->arr_nodes, list_ptr->arr_nodes + list_ptr->index_free);
    fprintf (file_graph, "\"%p\"->\"%p\"\n", list_ptr->arr_nodes, list_ptr->arr_nodes + list_ptr->index_head);

    for (size_t i = 1; i < list_ptr->capacity; i++)
    {
        if (isnan(list_ptr->arr_nodes[i].value))
        {
            fprintf (file_graph, "\"%p\" [label = \"{free|{%d|%d|%d}}\", fillcolor = white];\n",
                     list_ptr->arr_nodes + i, list_ptr->arr_nodes[i].index_prev, i, list_ptr->arr_nodes[i].index_next);
        }
        else
        {
            fprintf (file_graph, "\"%p\" [label = \"{%lg|{%d|%d|%d}}\"];\n",
                     list_ptr->arr_nodes + i, list_ptr->arr_nodes[i].value, list_ptr->arr_nodes[i].index_prev, i, list_ptr->arr_nodes[i].index_next);
        }

        fprintf (file_graph, "\"%p\"->\"%p\" [color = white]\n", list_ptr->arr_nodes + i - 1, list_ptr->arr_nodes + i);
    }

    for (size_t i = 1; i < list_ptr->capacity; i++)
    {
        if (i == list_ptr->index_head)
            fprintf (file_graph, "\"%p\"->\"%p\"\n", list_ptr->arr_nodes + list_ptr->index_head, list_ptr->arr_nodes + list_ptr->arr_nodes[i].index_next);
        else
        {
            if (i != list_ptr->index_free)
                fprintf (file_graph, "\"%p\"->\"%p\"\n", list_ptr->arr_nodes + i, list_ptr->arr_nodes + list_ptr->arr_nodes[i].index_prev);
            fprintf (file_graph, "\"%p\"->\"%p\"\n", list_ptr->arr_nodes + i, list_ptr->arr_nodes + list_ptr->arr_nodes[i].index_next);
        }
    }

    fprintf (file_graph, "}");

    int result_close = fclose (file_graph);

    system ("dot -Tjpg DumpGraph_list_physical.txt > DumpGraph_list_physical.jpg");
    system ("start DumpGraph_list_physical.jpg");

    return (result_close == EOF) ? ERROR_LOG_FILE : OK;
}




error_t Dump_Graph_Logical (smart_list* list_ptr)
{
    assert (list_ptr);
    assert (list_ptr->arr_nodes);

    FILE* file_graph = fopen ("DumpGraph_list_logical.txt", "w");

    fprintf (file_graph, "digraph G {\n");
    fprintf (file_graph, "node [shape = \"record\", style = \"filled\", color = \"#A80800\", fillcolor = \"#C0FFEE\"];\n");

    fprintf (file_graph, "\"%p\" [label = \"{BEGIN}\"];\n", list_ptr->arr_nodes);
    fprintf (file_graph, "\"%p\"->\"%p\"\n", list_ptr->arr_nodes, list_ptr->arr_nodes + list_ptr->index_head);

    size_t i = list_ptr->index_head;

    while (i != 0)
    {
        fprintf (file_graph, "\"%p\" [label = \"{%lg|{%d|%d|%d}}\"];\n",
                list_ptr->arr_nodes + i, list_ptr->arr_nodes[i].value, list_ptr->arr_nodes[i].index_prev, i, list_ptr->arr_nodes[i].index_next);

        if (i != list_ptr->index_head)
            fprintf (file_graph, "\"%p\"->\"%p\"\n", list_ptr->arr_nodes + i, list_ptr->arr_nodes + list_ptr->arr_nodes[i].index_prev);

        fprintf (file_graph, "\"%p\"->\"%p\"\n", list_ptr->arr_nodes + i, list_ptr->arr_nodes + list_ptr->arr_nodes[i].index_next);

        i = list_ptr->arr_nodes[i].index_next;
    }

    fprintf (file_graph, "}");

    int result_close = fclose (file_graph);

    system ("dot -Tjpg DumpGraph_list_logical.txt > DumpGraph_list_logical.jpg");
    system ("start DumpGraph_list_logical.jpg");

    return (result_close == EOF) ? ERROR_LOG_FILE : OK;
}




error_t List_OK (smart_list* list_ptr)
{
    if (list_ptr == NULL)
        return NULL_LIST_PTR;

    if (list_ptr->arr_nodes == NULL)
        return NULL_ARR_NODES;

    if (list_ptr->size_list > list_ptr->capacity - 1)
        return CAPACITY_LESS_SIZE;

    if (!isnan(list_ptr->arr_nodes[0].value))
        return ZERO_NODE_IS_NOT_NAN;

    if (list_ptr->arr_nodes[0].index_prev != 0)
        return ZERO_NODE_PREV_INCORRECT;

    if (list_ptr->arr_nodes[0].index_next != 0)
        return ZERO_NODE_NEXT_INCORRECT;

    if (list_ptr->arr_nodes[list_ptr->index_head].index_prev != 0)
        return HEAD_NODE_INCORRECT;

    if (list_ptr->arr_nodes[list_ptr->index_tail].index_next != 0)
        return TAIL_NODE_INCORRECT;

    if (list_ptr->arr_nodes[list_ptr->index_free].index_prev != 0)
        return FREE_NODE_INCORRECT;

    size_t elem = list_ptr->index_free;

    while (list_ptr->arr_nodes[elem].index_next != 0)
    {
        if (!isnan(list_ptr->arr_nodes[elem].value))
            return FREE_IS_NOT_NAN;
        elem = list_ptr->arr_nodes[elem].index_next;
    }

    return OK;
}




error_t Dump_Text (smart_list* list_ptr)
{
    error_t result = List_OK (list_ptr);

    char error[MAX_ERROR_NAME] = {};

    switch (result)
    {
        case (OK):
        {
            strcpy (error, "OK");
            break;
        }

        case (NULL_LIST_PTR):
        {
            strcpy (error, "NULL_LIST_PTR");
            break;
        }

        case (NULL_ARR_NODES):
        {
            strcpy (error, "NULL_ARR_NODES");
            break;
        }

        case (CAPACITY_LESS_SIZE):
        {
            strcpy (error, "CAPACITY_LESS_SIZE");
            break;
        }

        case (ZERO_NODE_IS_NOT_NAN):
        {
            strcpy (error, "ZERO_NODE_IS_NOT_NAN");
            break;
        }

        case (ZERO_NODE_PREV_INCORRECT):
        {
            strcpy (error, "ZERO_NODE_PREV_INCORRECT");
            break;
        }

        case (ZERO_NODE_NEXT_INCORRECT):
        {
            strcpy (error, "ZERO_NODE_NEXT_INCORRECT");
            break;
        }

        case (HEAD_NODE_INCORRECT):
        {
            strcpy (error, "HEAD_NODE_INCORRECT");
            break;
        }

        case (TAIL_NODE_INCORRECT):
        {
            strcpy (error, "TAIL_NODE_INCORRECT");
            break;
        }

        case (FREE_NODE_INCORRECT):
        {
            strcpy (error, "FREE_NODE_INCORRECT");
            break;
        }

        case (FREE_IS_NOT_NAN):
        {
            strcpy (error, "FREE_IS_NOT_NAN");
            break;
        }

        default:
        {
            strcpy (error, "NOT_KNOWN_ERROR");
            break;
        }
    }

    FILE* Log_File = fopen ("Log_File.txt", "w");
    assert (Log_File != NULL);

    fprintf (Log_File, "\nList_ptr (%s) [%p]\n\n", error, list_ptr);

    fprintf (Log_File, "size     = %u\n", list_ptr->size_list);
    fprintf (Log_File, "capacity = %u\n", list_ptr->capacity);
    fprintf (Log_File, "arr_nodes [%p]\n", list_ptr->arr_nodes);
    fprintf (Log_File, "{\n\n");

    for (size_t i = 0; i < list_ptr->capacity; i++)
    {
        if (! isnan(list_ptr->arr_nodes[i].value))
            fprintf (Log_File, "\t* [%u] = %lg\n", i, list_ptr->arr_nodes[i].value);
        else
            fprintf (Log_File, "\t  [%u] = %lg\n", i, list_ptr->arr_nodes[i].value);

        fprintf (Log_File, "\tprev_index = %u\n", list_ptr->arr_nodes[i].index_prev);
        fprintf (Log_File, "\tnext_index = %u\n\n", list_ptr->arr_nodes[i].index_next);
    }

    fprintf (Log_File, "}");

    int result_close = fclose (Log_File);

    return (result_close == EOF) ? ERROR_LOG_FILE : OK;
}




void Dump_All (smart_list* list_ptr)
{
    assert (list_ptr);

    assert (Dump_Graph_Physical (list_ptr) == OK);
    assert (Dump_Graph_Logical  (list_ptr) == OK);
    assert (Dump_Text           (list_ptr) == OK);

}
