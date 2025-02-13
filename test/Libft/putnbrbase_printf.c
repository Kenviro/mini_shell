/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbrbase_printf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:59:48 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/26 11:04:45 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len(unsigned int nbr, const char *base)
{
	int	base_len;
	int	i;

	i = 0;
	base_len = ft_strlen(base);
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= base_len;
		i++;
	}
	return (i);
}

void	ft_putnbrbase_printf(unsigned int nbr, const char *base, int *length)
{
	int				i;
	char			*result;

	i = len(nbr, base);
	result = ft_calloc((i + 1), sizeof(char));
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
	i = 0;
	while (result[i])
	{
		write(1, &result[i++], 1);
		(*length)++;
	}
	free (result);
}
