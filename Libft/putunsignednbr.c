/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunsignednbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:46:37 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/26 11:13:57 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_unsignedputnbr_fd(unsigned int n, int fd, int *length)
{
	int		i;
	char	nb[12];

	i = 11;
	nb[i--] = '\0';
	if (n == 0)
		nb[i--] = '0';
	while (n > 0)
	{
		nb[i] = (n % 10) + 48;
		n /= 10;
		i--;
	}
	write(fd, &nb[i + 1], 11 - i - 1);
	(*length) += (11 - i - 1);
}
