/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holy_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:35:54 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/21 15:06:43 by psoulie          ###   ########.fr       */
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

static char	*word(char *str, int start, char c)
{
	int		i;
	int		len;
	char	*word;
	int		in_quote[2];

	in_quote[0] = 0;
	in_quote[1] = 0;
	i = 0;
	len = ft_splitonsteroids(str, start, c);
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
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
		return (free(word), NULL);
	word[i] = 0;
	return (word);
}

char	**holy_split(char *str, char c)
{
	size_t	i;
	size_t	nbstr;
	char	**spliff;
	int		in_quote[2];

	spliff = malloc((count((char *)str, c) + 1) * sizeof(char *));
	if (!spliff)
		return (NULL);
	in_quote[0] = 0;
	in_quote[1] = 0;
	i = 0;
	nbstr = 0;
	while (str && str[i])
	{
		if (str[i] != c)
		{
			quote(str[i], &in_quote);
			spliff[nbstr] = word(str, i++, c);
			if (spliff[nbstr] == NULL)
				return (dup2(2, 1), ft_printf("trailing quote\n"), free(spliff), NULL);
			nbstr++;
			while (str[i] && (str[i] != c || in_quote[0] || in_quote[1]))
				quote(str[i++], &in_quote);
		}
		while (str[i] == c && (!in_quote[0] || !in_quote[1]))
			i++;
	}
	if (in_quote[0] || in_quote[1])
		return (dup2(2, 1), ft_printf("trailing quote\n"), free(spliff), NULL);
	return (spliff[nbstr] = NULL, spliff);
}
