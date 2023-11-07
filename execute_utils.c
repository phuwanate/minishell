/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:53:16 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/07 19:09:33 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execeve_fail(t_data *data)
{
	free_everything(data);
	ft_putendl_fd("minishell: execution command error", 2);
	exit(1);
}