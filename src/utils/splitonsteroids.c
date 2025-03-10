/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitonsteroids.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:07:01 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/10 15:45:03 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_splitonsteroids(char *str, int start, char c)
{
	int	len;
	int	i;
	int	in_quote[2];

	len = 0;
	i = 0;
	in_quote[0] = 0;
	in_quote[1] = 0;
	while (str[start + len + i] && (str[start + len + i] != c ||
			in_quote[0] || in_quote[1]))
	{
		if (quote(str[start + len + i], &in_quote))
		{
			len--;
			i++;
		}
		len ++;
	}
	return (len);
}
