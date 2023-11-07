/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:45:03 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/07 21:28:46 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int flag_check(t_token_node *curr_token)
{
    size_t  i;

    if(curr_token->value[0] != '-')
        return (FALSE);
    i = 1;
    while (curr_token->value[i])
    {
        if (curr_token->value[i] != 'n')
            return(FALSE);
        i++;
    }
    return (TRUE);
}

void echo_words(t_data *data, t_token_node *curr_token)
{
    (void)data;    
    
    if (curr_token == NULL)
        printf("\n");
    else if (flag_check(curr_token) == FALSE)
    {
        while (curr_token != NULL)
        {
            if (curr_token->next == NULL)
            {
                ft_putendl_fd(curr_token->value, 1);
                break ;
            }
            ft_putstr_fd(curr_token->value, 1);
            if (curr_token->next != NULL)
                ft_putstr_fd(" ", 1);
            curr_token = curr_token->next;
        }
    }
    else if (curr_token->next != NULL)
    {
        curr_token = curr_token->next;
        while (curr_token != NULL)
        {
            ft_putstr_fd(curr_token->value, 1);
            if (curr_token->next != NULL)
                ft_putstr_fd(" ", 1);
            curr_token = curr_token->next;
        }
    }
    return ;
}