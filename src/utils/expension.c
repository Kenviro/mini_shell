/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:30:30 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/13 15:02:41 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_getenv(char *key, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] == key[j])
			j++;
		if (env[i][j] == '=' && key[j] == '\0')
			return (ft_strdup(&env[i][j + 1]));
		i++;
	}
	return (NULL);
}

static char	*replace_mark(char *input, int i, int ms_status)
{
	char	*new_input;
	char	*beg;
	char	*value;
	char	*suffix;

	if (i != 0)
		beg = ft_substr(input, 0, i);
	else
		beg = ft_strdup("");
	if (!beg)
		return (NULL);
	value = ft_itoa(ms_status);
	if (!value)
		return (free(beg), NULL);
	new_input = ft_strjoin(beg, value);
	if (!new_input)
		return (NULL);
	if (input[i + 2])
		suffix = ft_strdup(&input[i + 2]);
	else
		suffix = ft_strdup("");
	if (!suffix)
		return (free(beg), free(value), free(new_input), NULL);
	input = ft_strjoin(new_input, suffix);
	return (free(beg), free(value), free(new_input), free(suffix), input);
}

static char	*get_expanded_input(char *input, int i, int j, char *expanded_value)
{
	char	*new_input;
	char	*beg;
	char	*temp;

	if ((i != 0))
		beg = ft_substr(input, 0, i);
	else
		beg = ft_strdup("");
	if (!beg)
		return (NULL);
	temp = ft_strjoin(beg, expanded_value);
	free(beg);
	if (!temp)
		return (NULL);
	if (input[j])
		new_input = ft_strjoin(temp, &input[j]);
	else
		new_input = ft_strdup(temp);
	free(temp);
	free(input);
	return (new_input);
}

static char	*replace_variable(char *input, int i, int j, char **env)
{
	char	*name_env;
	char	*expanded_value;
	char	*new_input;

	name_env = ft_substr(input, i + 1, j - i - 1);
	if (!name_env)
		return (NULL);
	expanded_value = ft_getenv(name_env, env);
	free(name_env);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	if (!expanded_value)
		return (NULL);
	new_input = get_expanded_input(input, i, j, expanded_value);
	free(expanded_value);
	return (new_input);
}

char	*expension(char *input, char **env, int ms_status, int i)
{
	int	j;

	if (input[i] == '$')
	{
		j = i;
		if (input[j + 1] == '?' && \
			(input[j + 2] == ' ' || input[j + 2] == '\0'))
			input = replace_mark(input, i, ms_status);
		else
		{
			j++;
			while (input[j] && input[j] != ' ' && input[j] != '\'' && \
				input[j] != '"' && input[j] != '$' && input[j] != '\n')
				j++;
			if (j - i > 1)
				input = replace_variable(input, i, j, env);
			else
				input[i] = ' ';
		}
	}
	return (input);
}
