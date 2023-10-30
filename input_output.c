/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:22:20 by plertsir          #+#    #+#             */
/*   Updated: 2023/10/30 16:10:22 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first.h"



int	open_heredoc(t_token_node *curr_token, t_data *data)
{
	size_t	len_doc;
	char	*in_doc;
    char    *ptr;
    int     pipe_fd[2];
	int		fd;
    
    if(pipe(pipe_fd) == -1)
        dprintf(2, "Pipe here_doc fail\n");
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		in_doc = get_next_line(STDIN_FILENO);
        len_doc = ft_strlen(in_doc);
		if (end_doc(in_doc, curr_token->value) == 0)
		{
			free(in_doc);
            break ;
		}
        ft_putstr_fd(in_doc, pipe_fd[1]);
        // write(pipe_fd[1], "\n", 1);
		free(in_doc);
	}
    close(pipe_fd[1]);
    return(pipe_fd[0]);
}

int check_infile(t_token_node *curr_token, t_data *data)
{
    size_t len_infile = 0;

    while (curr_token != NULL)
    {
        if(ft_strcmp(curr_token->type, "<") == 0)
        {
            data->fd_in = open(curr_token->value, O_RDONLY);
            if (data->fd_in == -1)
                file_error(curr_token->value);
        }
        else if(ft_strcmp(curr_token->type, "<<") == 0)
        {
            data->fd_in = curr_token->here_doc_fd;
        }
        curr_token = curr_token->next;
    }
    dup2(data->fd_in, STDIN_FILENO);
    close(data->fd_in);
    return (0);
}

int check_outfile(t_token_node *curr_token, t_data *data)
{
    size_t len_outfile = 0;
    int i = 1;

    while (curr_token->next != NULL)
    {
        curr_token = curr_token->next;
    }
    dprintf(2, "outfile: %s\n", curr_token->value);
    len_outfile = ft_strlen(curr_token->type);
    if(ft_strncmp(curr_token->type, ">", len_outfile) == 0)
    {
        data->fd_out = open(curr_token->value, O_TRUNC | O_WRONLY | O_CREAT, 0644);
    }
    else if(ft_strncmp(curr_token->type, ">>", len_outfile) == 0)
    {   
        data->fd_out = open(curr_token->value, O_APPEND | O_WRONLY | O_CREAT, 0644);
    }
    if (data->fd_out == -1)
        file_error(curr_token->value);
    dup2(data->fd_out, STDOUT_FILENO);
    close(data->fd_out);
    return (0);
}

int check_here_doc(t_list_node *curr_list, t_data *data)
{
    t_token_node *curr_token;
    curr_token = curr_list->infile;
    while (curr_list != NULL)
    {
        curr_token = curr_list->infile;
        while (curr_token != NULL)
        {    
            if (ft_strcmp(curr_token->type, "<<") == 0)
            {
                curr_token->here_doc_fd = open_heredoc(curr_token, data);
            }
            curr_token = curr_token->next;
        }
        curr_list = curr_list->next;
    }
    return (0);
}