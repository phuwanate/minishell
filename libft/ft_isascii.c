#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int main(void)
{
	char	str[] = "ABcD123?s";
	int	asc = 0, ft = 0, i = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if(isascii(str[i]) != 0)
			asc++;
		if(ft_isascii(str[i]) != 0)
			ft++;
	}
	printf("isascii = %d\n", asc);
	printf("ft_isascii = %d", ft);
}*/