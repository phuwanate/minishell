/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:48:09 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/05 22:16:45 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_error(t_data *data, char *file)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	if (data->builtin_parent == 1)
		data->errnum = 1;
	else
		exit(1);
}

void	path_error(t_data *data, t_token_node *curr_token)
{
	ft_putstr_fd(curr_token->value, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("No such file or directory", 2);
	// free_2d(path);
	// free_mem(data, 127);
	if (data->builtin_parent == 1)
		data->errnum = 1;
	else
		exit(127);
}

void	cmd_error(t_data *data, t_token_node *curr_token)
{
	(void)data;
	ft_putstr_fd(curr_token->value, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("command not found", 2);
	// free_2d(spl_av);
	// free_mem(data, 127);
	exit(127);
}
