/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holy_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:35:54 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/21 16:48:28 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	toggle_quote(int (*in_quote)[2], char quote)
{
	if (quote == '\'')
	{
		if (!(*in_quote)[1])
		{
			(*in_quote)[0] = !(*in_quote)[0];
			return (1);
		}
	}
	else
	{
		if (!(*in_quote)[0])
		{
			(*in_quote)[1] = !(*in_quote)[1];
			return (1);
		}
	}
	return (0);
}

int	quote(char c, int (*in_quote)[2])
{
	if (c == '\"' || c == '\'')
	{
		if (toggle_quote(in_quote, c))
			return (1);
	}
	return (0);
}

static int	count(char *str, char c)
{
	int	i;
	int	count;
	int	in_quote[2];

	if (!str)
		return (-1);
	in_quote[0] = 0;
	in_quote[1] = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			quote(str[i], &in_quote);
			count++;
			i++;
			while (str[i] && (str[i] != c || in_quote[0] || in_quote[1]))
				quote(str[i++], &in_quote);
		}
		while (str[i] == c && (!in_quote[0] || !in_quote[1]))
			i++;
	}
	return (count);
}

char	*word(char *str, int start, char c)
{
	int		len;
	char	*word;

	len = ft_splitonsteroids(str, start, c);
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	word = set_word(word, start, len, str);
	if (!word)
		return (free(word), NULL);
	return (word);
}

char	**holy_split(char *str, char c)
{
	size_t	nbstr;
	char	**spliff;
	int		in_quote[2];

	in_quote[0] = 0;
	in_quote[1] = 0;
	nbstr = 0;
	spliff = malloc((count((char *)str, c) + 1) * sizeof(char *));
	if (!spliff)
		return (NULL);
	spliff = big_loop(str, spliff, nbstr, &in_quote);
	return (spliff);
}
