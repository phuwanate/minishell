/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:53:15 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/03 10:04:09 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin_parent(t_data *data, t_list_node *curr_list)
{
	data->builtin_parent = 1;
	if (curr_list->cmd == NULL)
		return (data->builtin_parent = 0, FALSE);
	if (ft_strcmp(curr_list->cmd->value, "cd") == 0)
		change_dir(data, curr_list);
	else if (ft_strcmp(curr_list->cmd->value, "exit") == 0)
		go_exit(data, curr_list);
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