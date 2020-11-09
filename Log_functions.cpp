#include "List.h"

void Dump_Graph_Physical (smart_list* list_ptr)
{
    assert (list_ptr);
    assert (list_ptr->arr_nodes);

    FILE* file_graph = fopen ("DumpGraph_list_physical.txt", "w");

    fprintf (file_graph, "digraph G {\n");
    fprintf (file_graph, "node [shape = \"record\", style = \"filled\", color = \"#A80800\", fillcolor = \"#C0FFEE\"];\n");

    fprintf (file_graph, "\"%p\" [label = \"{BEGIN}\"];\n", list_ptr->arr_nodes);
    fprintf (file_graph, "\"%p\"->\"%p\"\n", list_ptr->arr_nodes, list_ptr->arr_nodes + list_ptr->index_free);

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

    fclose (file_graph);

    system ("dot -Tjpg DumpGraph_list_physical.txt > DumpGraph_list_physical.jpg");
    system ("start DumpGraph_list_physical.jpg");
}




void Dump_Graph_Logical (smart_list* list_ptr)
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

    fclose (file_graph);

    system ("dot -Tjpg DumpGraph_list_logical.txt > DumpGraph_list_logical.jpg");
    system ("start DumpGraph_list_logical.jpg");

}
