/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trailing_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:40:02 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/11 18:28:27 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	which_quote(int in_quote[2])
{
	if (in_quote[0])
		return ('\'');
	else if (in_quote[1])
		return ('"');
	else
		return (0);
}

char	check_quote(char *word, char quote)
{
	int		i;

	i = 0;
	while (word[i])
	{
		if (word[i] == quote)
		{
			quote = 0;
			i++;
		}
		if (!quote && (word[i] == '"' || word[i] == '\''))
			quote = word[i];
		i++;
	}
	return (quote);
}

char	*trailing_quote(char *word, int in_quote[2])
{
	char	quote;
	char	*new_word;
	char	*line;
	char	*tg;

	quote = which_quote(in_quote);
	new_word = ft_strjoin("\n", word);
	while (1)
	{
		line = get_next_line(0);
		tg = ft_strdup(new_word);
		free(new_word);
		new_word = ft_strjoin(tg, line);
		free(tg);
		quote = check_quote(new_word, quote);
		printf("test %s\n", new_word);
		if (!quote)
			return (new_word);
		free(line);
	}
}
