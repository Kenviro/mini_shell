/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:59:16 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/21 15:02:18 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*put_space(char *input, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(input, 0, i);
	tmp2 = ft_strdup(" ");
	tmp3 = ft_strdup(input + i);
	free(input);
	input = ft_strjoin(tmp, tmp2);
	free(tmp);
	tmp = ft_strjoin(input, tmp3);
	free(input);
	free(tmp2);
	free(tmp3);
	return (tmp);
}

static int	check_input(char *input, int *i)
{

	if ((input[*i] == '<' || input[*i] == '>' || input[*i] == '|') && \
		input[*i + 1] == input[*i])
	{
		if (input[*i + 2] != ' ')
		{
			*i = *i + 1;
			return (2);
		}
		*i = *i + 2;
	}
	if ((input[*i] == '<' || input[*i] == '>' || input[*i] == '|') && \
		input[*i + 1] != input[*i])
	{
		if (input[*i + 1] != ' ')
			return (1);
		*i = *i + 1;
	}
	return (0);
}

static char	*start_check(char *input, int *i)
{
	if (*i != 0 && (input[*i - 1] != ' ' && input[*i - 1] != input[*i]))
	{
		input = put_space(input, *i);
		return (input);
	}
	else if (check_input(input, i) == 2)
		return (put_space(input, *i + 1));
	else if (check_input(input, i) == 1)
		return (put_space(input, *i + 1));
	return (input);
}

char	*split_redirection(char *input)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (quote == 0 && (input[i] == '\'' || input[i] == '\"'))
		{
			quote = 1;
			i++;
		}
		if (quote == 0 && (input[i] == '>' || input[i] == '<' || \
			input[i] == '|'))
		{
			input = start_check(input, &i);
		}
		if (quote == 1 && (input[i] == '\'' || input[i] == '\"'))
			quote = 0;
		i++;
	}
	return (input);
}
