/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitonsteroids.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:07:01 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/21 16:47:38 by psoulie          ###   ########.fr       */
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

char	**big_loop(char *str, char **spliff, int nbstr, int (*in_quote)[2])
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ')
		{
			quote(str[i], in_quote);
			spliff[nbstr] = word(str, i++, ' ' );
			if (spliff[nbstr] == NULL)
				return (dup2(2, 1), ft_printf("trailing quote\n"), \
					free_2d(&spliff), NULL);
			nbstr++;
			while (str[i] && (str[i] != ' ' || \
				(*in_quote)[0] || (*in_quote)[1]))
				quote(str[i++], in_quote);
		}
		while (str[i] == ' ' && (!(*in_quote)[0] || !(*in_quote)[1]))
			i++;
	}
	if ((*in_quote)[0] || (*in_quote)[1])
		return (dup2(2, 1), ft_printf("trailing quote\n"), \
			spliff[nbstr] = NULL, free_2d(&spliff), NULL);
	spliff[nbstr] = NULL;
	return (spliff);
}
