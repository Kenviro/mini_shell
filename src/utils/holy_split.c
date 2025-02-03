/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holy_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:35:54 by psoulie           #+#    #+#             */
/*   Updated: 2025/02/03 17:10:25 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	toggle_quote(int *in_quote)
{
	*in_quote = !*in_quote;
}

int	quote(char c, int *in_quote)
{
	if (c == '\"' || c == '\'')
	{
		toggle_quote(in_quote);
		return (1);
	}
	return (0);
}

static int	count(char *str, char c)
{
	int	i;
	int	count;
	int	in_quote;

	in_quote = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			quote(str[i], &in_quote);
			count++;
			i++;
			while (str[i] && (str[i] != c || in_quote))
			{
				quote(str[i], &in_quote);
				i++;
			}
		}
		while (str[i] == c && !in_quote)
			i++;
	}
	return (count);
}

static char	*word(char *str, int start, char c)
{
	int		i;
	int		len;
	char	*word;
	int		in_quote;

	in_quote = 0;
	i = 0;
	len = ft_splitonsteroids(str, start, c);
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (quote(str[start + i], &in_quote))
			start++;
		word[i] = str[start + i];
		i++;
	}
	if (quote(str[start + i], &in_quote) < 2 && in_quote)
		return (dup2(2, 1), ft_printf("trailing quote\n"), exit(1), NULL);
	word[i] = 0;
	return (word);
}

char	**holy_split(char *str, char c)
{
	size_t	i;
	size_t	nbstr;
	char	**spliff;
	int		in_quote;

	spliff = malloc((count((char *)str, c) + 1) * sizeof(char *));
	if (!spliff)
		return (NULL);
	in_quote = 0;
	i = 0;
	nbstr = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			quote(str[i], &in_quote);
			spliff[nbstr++] = word(str, i, c);
			i++;
			while (str[i] && (str[i] != c || in_quote))
				quote(str[i++], &in_quote);
		}
		while (str[i] == c && !in_quote)
			i++;
	}
	return (spliff[nbstr] = NULL, spliff);
}
