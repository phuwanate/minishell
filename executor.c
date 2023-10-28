#include "first.h"

int check_infile(t_token_node *curr_token, t_data *data)
{
    size_t len_infile = 0;
    int i = 1;

    while (curr_token != NULL)
    {
        len_infile = ft_strlen(curr_token->type);
        // dprintf(1,"child %d { ", i);
        if(ft_strncmp(curr_token->type, "<", len_infile) == 0)
            *data->fd_in = open(curr_token->value, O_RDONLY);
            // dprintf(1,"type [%s] : value [%s] }\n", curr_token->type, curr_token->value);//open infile
        else if(ft_strncmp(curr_token->type, "<<", len_infile) == 0)
        {}    // dprintf(1,"type [%s] : value [%s] }\n", curr_token->type, curr_token->value);//open heredoc
        curr_token = curr_token->next;
        i++;
    }
    return (0);
}

int check_outfile(t_token_node *curr_token, t_data *data)
{
    size_t len_outfile = 0;
    int i = 1;

    while (curr_token != NULL)
    {
        len_outfile = ft_strlen(curr_token->type);
        // dprintf(1,"child %d { ", i);
        if(ft_strncmp(curr_token->type, ">", len_outfile) == 0)
        {
            *data->fd_out = open(curr_token->value, O_TRUNC | O_WRONLY | O_CREAT, 0644);
            // dprintf(1,"type [%s] : value [%s] --> truncate }\n", curr_token->type, curr_token->value);
            dup2(*data->fd_out, STDOUT_FILENO);
            close(*data->fd_out);
        }
        else if(ft_strncmp(curr_token->type, ">>", len_outfile) == 0)
        {   
            *data->fd_out = open(curr_token->value, O_APPEND | O_WRONLY | O_CREAT, 0644);
            // dprintf(1,"type [%s] : value [%s] --> append }\n", curr_token->type, curr_token->value);
            dup2(*data->fd_out, STDOUT_FILENO);
            close(*data->fd_out);
        }
        curr_token = curr_token->next;
        i++;
    }
    return (0);
}

int executor(t_data *data)
{
    int i;
    int fd_pipe[2];
    t_list_node *curr_list;

    i = 0;
    curr_list = (*data->list_head);
    while (curr_list != NULL)
    {
        check_infile(curr_list->infile, data); // if found infile go open
        dup2(*data->fd_in, 0);
        close(*data->fd_in);
        check_outfile(curr_list->outfile, data);// if found outfile go open
        if(curr_list->next != NULL) 
        {
            dprintf(2, "here\n");
            pipe(fd_pipe);
            *data->fd_in = fd_pipe[0]; // init pipe[0] to stdin
            *data->fd_out = fd_pipe[1]; // init pipe[1] to stdout
            dup2(*data->fd_out, STDOUT_FILENO);
            close(*data->fd_out);
        }
        data->pid[i] = fork();
        if(data->pid[i] == 0)
            execve(curr_list->cmd[0], curr_list->cmd, data->env);
        curr_list = curr_list->next;
        i++;
    }
    i = 0;
    while(i < data->num_child)
        waitpid(data->pid[i++], &data->exit_status, WUNTRACED);
    return (WEXITSTATUS(data->exit_status));
}

int main(int ac, char *av[], char *env[])
{
    t_data data;

    data.env = env;
    make_token_center(&data);   
    dprintf(2, "%d\n", executor(&data));
}
    