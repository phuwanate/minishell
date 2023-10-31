/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:22:20 by plertsir          #+#    #+#             */
/*   Updated: 2023/10/31 16:29:19 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first.h"

int	open_heredoc(t_token_node *curr_token, t_data *data)
{
	size_t	len_doc;
	char	*in_doc;
    char    *ptr;
    int     heredoc_fd[2];
	int		fd;
    
    if (pipe(heredoc_fd) == -1)
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
        ft_putstr_fd(in_doc, heredoc_fd[1]);
		free(in_doc);
	}
    close(heredoc_fd[1]);
    return(heredoc_fd[0]);
}

int check_infile(t_token_node *curr_token, t_data *data)
{
    while (curr_token != NULL)
    {
        if (curr_token->mark == m_infile)
        {
            data->fd_in = open(curr_token->value, O_RDONLY);
            if (data->fd_in == -1)
                file_error(curr_token->value);
        }
        if (curr_token->mark == m_heredoc)
            data->fd_in = curr_token->here_doc_fd;
        curr_token = curr_token->next;
    }
    dup2(data->fd_in, STDIN_FILENO);
    close(data->fd_in);
    return (0);
}

int check_outfile(t_token_node *curr_token, t_data *data)
{
    while (curr_token != NULL)
    {
        if (curr_token->mark == m_out_trunc)
            data->fd_out = open(curr_token->value, O_TRUNC | O_WRONLY | O_CREAT, 0644);
        if (curr_token->mark == m_out_append)
            data->fd_out = open(curr_token->value, O_APPEND | O_WRONLY | O_CREAT, 0644);
        if (data->fd_out == -1)
            file_error(curr_token->value);
        curr_token = curr_token->next;
    }
    dup2(data->fd_out, STDOUT_FILENO);
    close(data->fd_out);
    return (0);
}

int check_here_doc(t_list_node *curr_list, t_data *data)
{
    t_token_node *curr_token;

    while (curr_list != NULL)
    {
        curr_token = curr_list->infile;
        while (curr_token != NULL)
        {    
            if (curr_token->mark == m_heredoc)
            {
                curr_token->here_doc_fd = open_heredoc(curr_token, data);
            }
            curr_token = curr_token->next;
        }
        curr_list = curr_list->next;
    }
    return (0);
}
