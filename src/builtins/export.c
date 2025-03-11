/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:58:49 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/11 17:46:54 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_realloc_env(char ***env, int size)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * size);
	if (!new_env)
		error("Malloc failed");
	while ((*env)[i])
	{
		new_env[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	new_env[i] = NULL;
	free(*env);
	return (new_env);
}

static int	cmp_env(char *key, char *env)
{
	char	*tmp;

	tmp = get_key(env);
	if (ft_strcmp(key, tmp) == 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

static char	check_env(char *key, char *value, char ***env)
{
	char	*tmp;
	int		i;

	i = -1;
	while ((*env)[++i])
	{
		if (cmp_env(key, (*env)[i]))
		{
			free((*env)[i]);
			tmp = ft_strjoin(key, value);
			(*env)[i] = ft_strdup(tmp);
			return (free(tmp), 0);
		}
	}
	tmp = ft_strjoin(key, value);
	(*env) = ft_realloc_env(env, i + 2);
	(*env)[i] = ft_strdup(tmp);
	(*env)[i + 1] = NULL;
	return (free(tmp), 0);
}

int	export(t_list *list, char ***env)
{
	t_list	*tmp;
	char	*key;
	char	*value;

	tmp = list;
	tmp = tmp->next;
	while (tmp)
	{
		key = get_key(tmp->content);
		value = get_value(tmp->content);
		check_env(key, value, env);
		free(key);
		free(value);
		tmp = tmp->next;
	}
	return (0);
}
