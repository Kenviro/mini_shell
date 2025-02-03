/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointerprintf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:59:31 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/26 11:05:02 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len(unsigned long long n, const char *base)
{
	size_t				len;
	unsigned long long	base_len;

	len = 1;
	base_len = ft_strlen(base);
	while (n >= base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

void	ft_pointer_printf(size_t nbr, const char *base, int *length)
{
	int				i;
	char			*result;

	i = ft_len(nbr, base);
	result = ft_calloc((i + 1), sizeof(char));
	write(1, "0x", 2);
	(*length) += 2;
	if (nbr == 0)
		result[--i] = '0';
	else
	{
		while (nbr > 0)
		{
			result[--i] = base[nbr % 16];
			nbr /= 16;
		}
	}
	while (result[i])
	{
		write(1, &result[i++], 1);
		(*length)++;
	}
	free(result);
}
