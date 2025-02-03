/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_printf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:06:06 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/26 11:04:50 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_printf(char c, int fd, int *length)
{
	write(fd, &c, 1);
	(*length)++;
}

void	ft_putstr_printf(char *s, int fd, int *length)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(fd, "(null)", 6);
		(*length) += 6;
		return ;
	}
	while (s[i])
	{
		ft_putchar_printf(s[i], fd, length);
		i++;
	}
}

int	loop_printf(int i, char n[12], int nb)
{
	while (nb > 0)
	{
		n[i] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	return (i);
}

void	ft_putnbr_printf(int n, int fd, int *length)
{
	int		i;
	int		j;
	char	nb[12];

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		(*length) += 11;
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
	i = loop_printf(i, nb, n);
	if (j == 1)
		nb[i--] = '-';
	write(fd, &nb[i + 1], 11 - i - 1);
	(*length) += (11 - i - 1);
}
