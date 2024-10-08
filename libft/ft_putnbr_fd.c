#include "libft.h"

void	ft_putnbr_fd(int num, int fd)
{
	if (num == -2147483648)
		write(fd, "-2147483648", 11);
	else if (num < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-num, fd);
	}
	else if (num > 9)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putchar_fd((num % 10) + '0', fd);
	}
	else
		ft_putchar_fd(num + '0', fd);
}
// output int (num) to the given (fd)