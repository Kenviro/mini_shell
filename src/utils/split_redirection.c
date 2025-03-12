/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:59:16 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/12 18:32:21 by ktintim-         ###   ########.fr       */
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
	if ((input[*i] == '|') && input[*i + 1] != ' ')
	{
		// *i = *i + 1;
		return (1);
	}
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
			if (check_input(input, &i) == 2)
				input = put_space(input, i + 1);
			else if (check_input(input, &i) == 1)
				input = put_space(input, i + 1);
		}
		if (quote == 1 && (input[i] == '\'' || input[i] == '\"'))
			quote = 0;
		i++;
	}
	return (input);
}
