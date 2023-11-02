/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:28:48 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/02 23:02:15 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Parent builtin: cd, export, unset, exit
//Child builtin: echo, pwd, env

void	change_dir(t_data *data, t_list_node *curr_list)
{
	if (curr_list->cmd->next != NULL)
	{
		if (chdir(curr_list->cmd->next->value) != -1)
			data->errnum = 0;
		else if (errno == 13)
			file_error(data, curr_list->cmd->next->value);
		else if (errno == 2)
			path_error(data, curr_list->cmd->next);
		else
		{
			ft_putstr_fd("cd", 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(curr_list->cmd->next->value, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd("Not a directory", 2);
			data->errnum = 1;
		}
	}
	else
		chdir(getenv("HOME"));
}

int	get_curr_dir(t_data *data)
{
	char curr_dir[PATH_MAX];
	
	if(!getcwd(curr_dir, PATH_MAX))
	{
		perror("getcwd");
		exit(1);
	}
	ft_putendl_fd(curr_dir, STDOUT_FILENO);
	return (data->errnum = 0, TRUE);
}

int	check_builtin_parent(t_data *data, t_list_node *curr_list)
{
	data->builtin_parent = 1;
	if (curr_list->cmd == NULL)
		return (data->builtin_parent = 0, FALSE);
	if (ft_strcmp(curr_list->cmd->value, "cd") == 0)
		change_dir(data, curr_list);
	else
		return (data->builtin_parent = 0, FALSE);
	return (TRUE);
}

int	check_builtin_child(t_data *data, t_list_node *curr_list)
{
	if (ft_strcmp(curr_list->cmd->value, "pwd") == 0)
		return(get_curr_dir(data), TRUE);
	return (FALSE);
}