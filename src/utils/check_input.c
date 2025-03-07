/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:00:16 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/07 11:50:37 by ktintim-         ###   ########.fr       */
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

static char	*new_input(char *input, int i, int j, char **env)
{
	char	*new_input;
	char	*beg;
	char	*new;
	char	*name_env;
	char	*value;

	beg = ft_substr(input, 0, i);
	name_env = ft_substr(input, i + 1, j - i - 1);
	value = ft_getenv(name_env, env);
	new = ft_strjoin(beg, value);
	free(beg);
	free(name_env);
	free(value);
	new_input = ft_strjoin(new, &input[j]);
	free(new);
	free(input);
	return (new_input);
}

char	*found_dollar(char *input, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			j = i;
			while (input[j] && input[j] != ' ')
				j++;
			if (j - i > 1)
			{
				input = new_input(input, i, j, env);
			}
			else
				input[i] = ' ';
		}
		i++;
	}
	return (input);
}
