/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:28:48 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/06 22:31:50 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Parent builtin: cd, export, unset, exit
//Child builtin: echo, pwd, env
//cd
void	change_dir(t_data *data, t_list_node *curr_list)
{
	if (curr_list->cmd->next != NULL)
	{
		if (chdir(curr_list->cmd->next->value) != -1)
			data->errnum = 0;
		else if (errno == 13)
			file_error(data, curr_list->cmd->next->value);
		else if (errno == 2)
			cd_path_error(data, curr_list->cmd->next);
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
		if(chdir(getenv("HOME")) == -1)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			data->errnum = 1;
		}
}
