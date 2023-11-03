/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:28:48 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/03 18:10:09 by plertsir         ###   ########.fr       */
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
	char	curr_dir[PATH_MAX];

	if (!getcwd(curr_dir, PATH_MAX))
	{
		perror("getcwd");
		exit(1);
	}
	ft_putendl_fd(curr_dir, STDOUT_FILENO);
	return (data->errnum = 0, TRUE);
}

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
				//need to free smth.
				exit((int)status);
			}
			else if (status_err == 2)
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
				ft_putendl_fd("too many arguments", STDOUT_FILENO);
				//need to free smth.
				data->errnum = (int)status;
			}
		}
		else
		{
			data->errnum = (int)status;
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(data->errnum);
		}
	}
	else
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
	//need to free smth.
		exit(0);
	}
}

