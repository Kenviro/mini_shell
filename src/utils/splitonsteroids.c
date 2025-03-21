/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitonsteroids.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:07:01 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/21 15:47:34 by psoulie          ###   ########.fr       */
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
	while (str[start + len + i] && (str[start + len + i] != c || \
			in_quote[0] || in_quote[1]))
	{
		if (quote(str[start + len + i], &in_quote))
		{
			i++;
			continue ;
		}
		len ++;
	}
	return (len);
}

char	*set_word(char *word, int start, int len, char *str)
{
	int	i;
	int	in_quote[2];

	in_quote[0] = 0;
	in_quote[1] = 0;
	i = 0;
	while (i < len)
	{
		if (quote(str[start + i], &in_quote))
		{
			start++;
			continue ;
		}
		word[i] = str[start + i];
		i++;
	}
	if (quote(str[start + i], &in_quote) < 2 && \
		(in_quote[0] || in_quote[1]) && !quote(str[start + i + 1], &in_quote))
		return (NULL);
	word[i] = 0;
	return (word);
}
