/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:28:48 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/15 14:44:09 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	home_err(t_data *data)
{
	ft_putendl_fd("cd: HOME not set", 2);
	data->errnum = 1;
}

static void	check_home(t_data *data)
{
	int		i;
	char	*home;
	char	*tmp;

	i = 0;
	home = NULL;
	while (data->env[i])
	{
		if (is_duplicate(data->env[i], "HOME=") == 1)
			home = data->env[i];
		i++;
	}
	if (!home)
		home_err(data);
	else
	{
		i = 0;
		while (home[i] != '=')
			i++;
		tmp = ft_strchr(home, '=');
		home = ft_substr(home, i + 1, ft_strlen(home) - (size_t)tmp);
		chdir(home);
		free(home);
	}
}

void	change_dir(t_data *data, t_list_node *curr_list)
{
	int		i;

	i = 0;
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
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(curr_list->cmd->next->value, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd("Not a directory", 2);
			data->errnum = 1;
		}
	}
	else
		check_home(data);
}

void	directory_err(t_data *data, t_list_node *curr_list)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(curr_list->cmd->next->value, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("Not a directory", 2);
	data->errnum = 1;
	free_everything(data);
	exit(1);
}

void	check_cd_err(t_data *data, t_list_node *curr_list)
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
			directory_err(data, curr_list);
	}
	else
	{
		check_home(data);
		free_everything(data);
		if (data->errnum == 1)
			exit(1);
		exit(0);
	}
}
