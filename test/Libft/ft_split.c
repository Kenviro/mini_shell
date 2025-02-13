/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:49:28 by ktintim-          #+#    #+#             */
/*   Updated: 2024/10/03 13:49:30 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_free_all(char **result, int words_allocated)
{
	int	i;

	i = 0;
	while (i < words_allocated)
	{
		if (result[i])
			free(result[i]);
		i++;
	}
	free(result);
}

int	nb_sep(char const *str, char sep)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] != sep && (i == 0 || str[i - 1] == sep))
			words++;
		i++;
	}
	return (words);
}

char	*ft_word_dup(char const *str, int *start, int finish)
{
	char	*word;
	int		j;
	int		s;

	s = *start;
	j = 0;
	word = (char *)malloc((finish - s + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (s < finish)
		word[j++] = str[s++];
	word[j] = '\0';
	*start = -1;
	return (word);
}

char	**allocate_result(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc((nb_sep(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i[3];

	i[0] = -1;
	i[1] = 0;
	i[2] = -1;
	result = allocate_result(s, c);
	if (!result)
		return (NULL);
	while (++i[0] <= ft_strlen(s))
	{
		if (s[i[0]] != c && i[2] < 0)
			i[2] = i[0];
		else if ((s[i[0]] == c || i[0] == ft_strlen(s)) && i[2] >= 0)
		{
			result[i[1]] = ft_word_dup(s, &i[2], i[0]);
			if (!result[i[1]++])
			{
				ft_free_all(result, i[1]);
				return (NULL);
			}
		}
	}
	result[i[1]] = 0;
	return (result);
}
