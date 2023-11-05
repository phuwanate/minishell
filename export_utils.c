/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:24:24 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/05 22:32:22 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void is_valid_ident(t_data *data, t_token_node *curr_token)
{
    int  i;

    i = 0;
    while(curr_token->value[i])
    {
        if (ft_isalpha(curr_token->value[i]) == 0)
        {
            ft_putstr_fd("export: `", 2);
            ft_putstr_fd(curr_token->value, 2);
            ft_putendl_fd("': not a valid identifier", 2);
            data->errnum = 1;
            return;
        }
        i++;
    }
}