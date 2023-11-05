/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:23:15 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/05 20:20:27 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_env(char **env_copy)
{
    size_t  i;

    i = 0;
    while(env_copy[i])
    {
        if (env_copy[i] != NULL)
        {
            free(env_copy[i]);
            env_copy[i] = NULL;
        }
        i++;
    }
    free(env_copy);
    env_copy = NULL;
}

static char *join_quote(char *env_copy)
{
    int i;
    char *tmp;
    char *combine;
    char *front;
    char *back;
    
    i = 0;
    while (env_copy[i] != '=')
        i++;
    tmp = ft_strchr(&env_copy[0], '=');
    front = ft_substr(&env_copy[0], 0, tmp - &env_copy[0] + 1);
    back = ft_substr(&env_copy[0], i + 1,  ft_strlen(env_copy) - (size_t)tmp);
    combine = ft_strjoin("\"", back);
    free(back);
    tmp = combine;
    combine = ft_strjoin(combine, "\"");
    free(tmp);
    tmp = combine;
    combine = ft_strjoin(front, combine);
    free(tmp);
    free(front);
    free(env_copy);
    return (combine);
}

void sort_env(t_data *data, char **env_copy)
{
    size_t  i;
    size_t  j;
    char    *tmp;
    
    i = 0;
    while (i < data->env_row_max - 1)
    {
        j = 0;
        while (j < data->env_row_max - i - 1)
        {
            if (ft_strcmp(env_copy[j], env_copy[j + 1]) > 0)
            {
                tmp = env_copy[j];
                env_copy[j] = env_copy[j + 1];
                env_copy[j + 1] = tmp;
            }
            j++;   
        }
        i++;
    }
}

int declare_env(t_data *data)
{
    size_t i;
    char **env_copy;
    
    i = 0;
    env_copy = (char **)ft_calloc(sizeof(char *), data->env_row_max + 1);
    while (i < data->env_row_max)
    {
        env_copy[i] = join_quote(ft_strdup(data->env[i]));
        i++;
    }
    sort_env(data, env_copy);
    i = 0;
    while(env_copy[i])
    {
        printf("declare -x %s\n", env_copy[i]);
        i++;
    }
    free_env(env_copy);
    return (TRUE);
}

int	export_new_env(t_data *data, t_token_node *curr_token)
{
    (void)data;
    
    if (curr_token == NULL || \
    ft_strchr(curr_token->value, '=') == NULL)
			return (FALSE);
	// if (curr_token == NULL)
	// 	return (declare_env(data));
    // while (curr_token->cmd != NULL)
    // {
            //export with argument
    // }
    return (FALSE);
}

//declare -x = make env available to child proc.