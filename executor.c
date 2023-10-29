#include "first.h"

int check_infile(t_token_node *curr_token, t_data *data)
{
    size_t len_infile = 0;
    int i = 1;

    while (curr_token != NULL)
    {
        len_infile = ft_strlen(curr_token->type);
        if(ft_strncmp(curr_token->type, "<", len_infile) == 0)
        {
            data->fd_in = open(curr_token->value, O_RDONLY);
            if (data->fd_in == -1)
                file_error(curr_token->value);
        }
        else if(ft_strncmp(curr_token->type, "<<", len_infile) == 0)
        {
            dprintf(1,"type [%s] : value [%s] }\n", curr_token->type, curr_token->value);//open heredoc
        }
        curr_token = curr_token->next;
        i++;
    }
    dup2(data->fd_in, STDIN_FILENO);
    close(data->fd_in);
    return (0);
}

int check_outfile(t_token_node *curr_token, t_data *data)
{
    size_t len_outfile = 0;
    int i = 1;

    while (curr_token != NULL)
    {
        len_outfile = ft_strlen(curr_token->type);
        if(ft_strncmp(curr_token->type, ">", len_outfile) == 0)
        {
            data->fd_out = open(curr_token->value, O_TRUNC | O_WRONLY | O_CREAT, 0644);
        }
        else if(ft_strncmp(curr_token->type, ">>", len_outfile) == 0)
        {   
            data->fd_out = open(curr_token->value, O_APPEND | O_WRONLY | O_CREAT, 0644);
        }
        curr_token = curr_token->next;
    }
    dup2(data->fd_out, STDOUT_FILENO);
    close(data->fd_out);
    return (0);
}

int executor(t_data *data)
{
    int i;
    int fd_pipe[2];
    t_list_node *curr_list;

    i = 0;
    //copy original I/O file.
    data->stdin_copy = dup(STDIN_FILENO);
    data->stdout_copy = dup(STDOUT_FILENO);
    curr_list = (*data->list_head);
    while (curr_list != NULL)
    {
        if (pipe(fd_pipe) == -1)
            printf("pipe error\n");
        data->pid[i] = fork();
        if(data->pid[i] == 0)
        {
            if(curr_list->infile != NULL)
            {
                check_infile(curr_list->infile, data);
            }
            if(curr_list->outfile != NULL)
            {
                check_outfile(curr_list->outfile, data);
            }
            else if(curr_list->next != NULL)  
            {
                if (dup2(fd_pipe[1], STDOUT_FILENO) == - 1)
                    dprintf(2, "duplicate outfile error\n");
                close(fd_pipe[0]);
                close(fd_pipe[1]);           
            }
            // dprintf(2, "%s %s\n", curr_list->cmd[0], curr_list->cmd[1]);
            execve(curr_list->cmd[0], curr_list->cmd, data->env);
        }
        else if(curr_list->next != NULL)
        {   
            if (dup2(fd_pipe[0], STDIN_FILENO) == - 1)
                dprintf(2, "duplicate infile error\n");
            close(fd_pipe[0]);
            close(fd_pipe[1]);
        }
        curr_list = curr_list->next;
        i++;
    }
    i = 0;
    while(i < data->num_child)
        waitpid(data->pid[i++], &data->exit_status, WUNTRACED);
    dup2(data->stdin_copy, STDIN_FILENO);
    dup2(data->stdout_copy, STDOUT_FILENO);
    data->exit_status = WEXITSTATUS(data->exit_status);
    return (data->exit_status);
}

int main(int ac, char *av[], char *env[])
{
    t_data data;

    data.env = env;
    make_token_center(&data);   
    executor(&data);
    return (data.exit_status);
}
    