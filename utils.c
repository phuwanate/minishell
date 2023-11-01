/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:24:24 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/01 09:47:34 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first.h"

void	path_cpy(char *dst, const char *src)
{
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	i = 0;
	while (i < len_src)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	end_doc(char *hay_stack, char *needle)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (hay_stack[i] != needle[i])
			break ;
		i++;
	}
	if ((hay_stack[i] != '\n') || (needle[i] != '\0'))
		return (1);
	else
		return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while ((ptr1[i] || ptr2[i]))
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
