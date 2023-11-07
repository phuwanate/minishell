/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:22:29 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/07 16:20:51 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//exit
void	go_exit(t_data *data, t_list_node *curr_list)
{
	unsigned char	status;
	int				status_err;

	(void)data;
	if (curr_list->cmd->next != NULL)
	{
		status_err = check_status(curr_list->cmd->next, &status);
		if (status_err != 0)
		{
			if (status_err == 1)
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
				ft_putstr_fd(curr_list->cmd->next->value, STDOUT_FILENO);
				ft_putstr_fd(": ", STDOUT_FILENO);
				ft_putendl_fd("numeric argument required", STDOUT_FILENO);
				free_everything(data);
				exit((int)status);
			}
			else if (status_err == 2)
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
				ft_putendl_fd("too many arguments", STDOUT_FILENO);
				data->errnum = (int)status;
			}
		}
		else
		{
			data->errnum = (int)status;
			ft_putendl_fd("exit", STDOUT_FILENO);
			free_everything(data);
			exit(data->errnum);
		}
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_everything(data);
	exit(0);
}