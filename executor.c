#include "first.h"

int check_infile(t_data *data)
{
    size_t len_infile = 0;
    t_token_node *curr;
    int i = 1;

    curr = (*data->list_head)->infile;
    while (curr != NULL)
    {
        len_infile = ft_strlen(curr->type);
        //printf("child %d { ", i);
        if(ft_strncmp(curr->type, "<", len_infile) == 0)
            data->fd_in = open(curr->value, O_RDONLY);
            //printf("type [%s] : value [%s] }\n", curr->type, curr->value);//open infile
        else if(ft_strncmp(curr->type, "<<", len_infile) == 0)
            printf("type [%s] : value [%s] }\n", curr->type, curr->value);//open heredoc
        curr = curr->next;
        i++;
    }
    return (0);
}

int check_outfile(t_data *data)
{
    size_t len_outfile = 0;
    t_token_node *curr;
    int i = 1;

    curr = (*data->list_head)->outfile;
    while (curr != NULL)
    {
        len_outfile = ft_strlen(curr->type);
        // printf("child %d { ", i);
        if(ft_strncmp(curr->type, ">", len_outfile) == 0)
            data->fd_out = open(curr->value, O_TRUNC | O_WRONLY | O_CREAT, 0644);
            //printf("type [%s] : value [%s] --> truncate }\n", curr->type, curr->value);
        else if(ft_strncmp(curr->type, ">>", len_outfile) == 0)
            data->fd_out = open(curr->value, O_APPEND | O_WRONLY | O_CREAT, 0644);
            //printf("type [%s] : value [%s] --> append }\n", curr->type, curr->value);
        curr = curr->next;
        i++;
    }
    return (0);
}

int executor(t_data *data)
{
    int i;
    int fd_pipe[2];

    i = 0;
    check_infile(data);
    while (i < data->num_child)
    {
        dup2(data->fd_in, 0);
        close(data->fd_in);
        if (i == data->num_child - 1)
        {
            if ((*data->list_head)->outfile != NULL)
                check_outfile(data);
        }
        else
        {
            pipe(fd_pipe);
            data->fd_in = fd_pipe[0];
            data->fd_out = fd_pipe[1];
        }
        i++;
    }
    return (0);
}

int main(int ac, char *av[], char *env[])
{
    t_data data;

    data.env = env;
    make_token_center(&data);   
    executor(&data);
    
    execve((*data.list_head)->cmd[0], (*data.list_head)->cmd, data.env);
}

    //char *test[] = {"/bin/cat", "cat", NULL};
    // execve((*data.list_head)->cmd[0], (*data.list_head)->cmd, data.env);
    //Debug token_center;
    // printf("%s\n", (*data.list_head)->infile->type);
    // printf("%s\n", (*data.list_head)->infile->value);
    // printf("%s\n", (*data.list_head)->outfile->type);
    // printf("%s\n", (*data.list_head)->outfile->value);
    
