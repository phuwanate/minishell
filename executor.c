#include "first.h"

void check_infile_outfile(t_list_node *curr_list, t_data *data)
{
    if (curr_list->infile != NULL)
        check_infile(curr_list->infile, data);
    if (curr_list->outfile != NULL)
        check_outfile(curr_list->outfile, data);
    else if (curr_list->next != NULL)  
    {
        if (dup2(data->fd_pipe[1], STDOUT_FILENO) == - 1)
            dprintf(2, "duplicate outfile error\n");
        close(data->fd_pipe[0]);
        close(data->fd_pipe[1]);           
    }
}

int prep_before_fork(t_data *data, t_list_node *curr_list)
{
    data->stdin_copy = dup(STDIN_FILENO);
    data->stdout_copy = dup(STDOUT_FILENO);
    check_here_doc(curr_list, data);
    data->fd_pipe = malloc(sizeof(int) * 2);
    if (!data->fd_pipe)
        return (printf("Error malloc pipe\n"), FALSE);
    return (TRUE);
}

int executor(t_data *data)
{
    int         i;
    t_list_node *curr_list;

    curr_list = data->list_head;
    i = 0;
    if (prep_before_fork(data, curr_list) == FALSE)
        return(FALSE);
    while (curr_list != NULL)
    {
        if (pipe(data->fd_pipe) == -1)
            dprintf(2, "pipe error\n");
        data->pid[i] = fork();
        if (data->pid[i] == 0)
        {
            check_infile_outfile(curr_list, data);
            execve(curr_list->cmd[0], curr_list->cmd, data->env);
        }
        else if (curr_list->next != NULL)
        {
            if (dup2(data->fd_pipe[0], STDIN_FILENO) == - 1)
                dprintf(2, "duplicate infile error\n");
            close(data->fd_pipe[0]);
            close(data->fd_pipe[1]);
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

    make_token_center(&data);  
    executor(&data);
    return (data.exit_status);
}
    