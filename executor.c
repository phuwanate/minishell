#include "first.h"

int check_infile(t_data *data)
{
    size_t len_infile = ft_strlen((*data->list_head)->infile->type);
    t_token_node *curr;
    int i = 1;

    curr = (*data->list_head)->infile;
    while (curr != NULL)
    {
        printf("child %d { ", i);
        if(ft_strncmp(curr->type, "<", len_infile) == 0)
            printf("type [%s] : value [%s] }\n", curr->type, curr->value);
        else if(ft_strncmp(curr->type, "<<", len_infile) == 0)
            printf("type [%s] : value [%s] }\n", curr->type, curr->value);
        curr = curr->next;
        i++;
    }
    return (0);
}

int check_outfile(t_data *data)
{
    size_t len_outfile = ft_strlen((*data->list_head)->outfile->type);
    t_token_node *curr;
    int i = 1;

    curr = (*data->list_head)->outfile;
    while (curr != NULL)
    {
        printf("child %d { ", i);
        if(ft_strncmp(curr->type, ">", len_outfile) == 0)
            printf("type [%s] : value [%s] --> truncate }\n", curr->type, curr->value);
        else if(ft_strncmp(curr->type, ">>", len_outfile) == 0)
            printf("type [%s] : value [%s] --> append }\n", curr->type, curr->value);
        curr = curr->next;
        i++;
    }
    return (0);
}

int executor(t_data *data)
{
    check_infile(data);
    check_outfile(data);
    return (0);
}

int main(int ac, char *av[], char *env[])
{
    t_data data;

    data.env = env;
    make_token_center(&data);   
    executor(&data);
}

    //Debug token_center;
    // printf("%s\n", (*data.list_head)->infile->type);
    // printf("%s\n", (*data.list_head)->infile->value);
    // printf("%s\n", (*data.list_head)->outfile->type);
    // printf("%s\n", (*data.list_head)->outfile->value);
    

    //execve((*data.list_head)->cmd[0], (*data.list_head->cmd), data.env);