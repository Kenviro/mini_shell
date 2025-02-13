/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:59:13 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/26 11:04:57 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	whatpr(char c, va_list *args, int *i, int *length)
{
	if (c == 'c')
		ft_putchar_printf(va_arg(*args, int), 1, length);
	else if (c == '%')
		ft_putchar_printf('%', 1, length);
	else if (c == 's')
		ft_putstr_printf(va_arg(*args, char *), 1, length);
	else if (c == 'i')
		ft_putnbr_printf(va_arg(*args, int), 1, length);
	else if (c == 'd')
		ft_putnbr_printf(va_arg(*args, int), 1, length);
	else if (c == 'u')
		ft_unsignedputnbr_fd(va_arg(*args, unsigned int), 1, length);
	else if (c == 'x')
		ft_putnbrbase_printf(va_arg(*args, unsigned int) \
							, "0123456789abcdef", length);
	else if (c == 'X')
		ft_putnbrbase_printf(va_arg(*args, unsigned int) \
							, "0123456789ABCDEF", length);
	else if (c == 'p')
		ft_pointer_printf(va_arg(*args, size_t) \
								, "0123456789abcdef", length);
	else
		(*i)--;
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		length;
	va_list	args;

	i = 0;
	length = 0;
	if (str == NULL)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			whatpr(str[i], &args, &i, &length);
			i++;
		}
		else
		{
			ft_putchar_printf(str[i], 1, &length);
			i++;
		}
	}
	va_end(args);
	return (length);
}
