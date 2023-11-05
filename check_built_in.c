/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:53:15 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/05 22:54:19 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin_parent(t_data *data, t_list_node *curr_list)
{
	// data->builtin_parent = 0;
	if (curr_list->cmd == NULL)
		return (data->builtin_parent = 0, FALSE);
	if (ft_strcmp(curr_list->cmd->value, "cd") == 0)
	{
		data->builtin_parent = 1;
		change_dir(data, curr_list);
	}
	else if (ft_strcmp(curr_list->cmd->value, "exit") == 0)
	{
		data->builtin_parent = 1;
		go_exit(data, curr_list);
	}
	else if (ft_strcmp(curr_list->cmd->value, "export") == 0)//parent do if has '=' in string.
	{
		data->builtin_parent = 1;
		if (export_new_env(data, curr_list->cmd->next) == FALSE)
			return (data->builtin_parent = 0, FALSE);
	}	
	else
		return (data->builtin_parent = 0, FALSE);
	return (TRUE);
}

int	check_builtin_child(t_data *data, t_list_node *curr_list)
{
	if (ft_strcmp(curr_list->cmd->value, "pwd") == 0)
		return (get_curr_dir(data), TRUE);
	return (FALSE);
}

int	before_child_exe(t_data *data, t_list_node *curr_list)
{
	unsigned char	status;
	
	if (ft_strcmp(curr_list->cmd->value, "cd") == 0)
		return (FALSE);
	else if (ft_strcmp(curr_list->cmd->value, "exit") == 0)
	{
		if (curr_list->cmd->next != NULL)
		{
			check_status(curr_list->cmd->next, &status);
			exit((int)status);
		}
		return (FALSE);
	}
	else if (ft_strcmp(curr_list->cmd->value, "export") == 0)
	{
		if (curr_list->cmd->next == NULL)
		{
			declare_env(data);
			exit(0);
		}
		is_valid_ident(data, curr_list->cmd->next);
		return (FALSE);
	}
	return (TRUE);
}
