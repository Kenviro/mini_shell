/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 09:59:48 by ktintim-          #+#    #+#             */
/*   Updated: 2024/10/03 09:59:50 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

int	loop(int i, char n[12], int nb)
{
	while (nb > 0)
	{
		n[i] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	int		j;
	char	nb[12];

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	j = 0;
	i = 11;
	nb[i--] = '\0';
	if (n == 0)
		nb[i--] = '0';
	if (n < 0 && n != -2147483648)
	{
		j++;
		n = -n;
	}
	i = loop(i, nb, n);
	if (j == 1)
		nb[i--] = '-';
	write(fd, &nb[i + 1], 11 - i - 1);
}
