/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitonsteroids.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:07:01 by psoulie           #+#    #+#             */
/*   Updated: 2025/02/03 17:10:28 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_splitonsteroids(char *str, int start, char c)
{
	int	len;
	int	i;
	int	in_quote;

	len = 0;
	i = 0;
	in_quote = 0;
	while (str[start + len + i] && (str[start + len + i] != c || in_quote))
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
