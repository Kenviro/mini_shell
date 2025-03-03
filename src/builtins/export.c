/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:58:49 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/03 16:39:07 by ktintim-         ###   ########.fr       */
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
	printf("tmp: %s\n", tmp);
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
	char	*key;
	char	*value;

	if (list->next->content == NULL)
		return (print_export(*env), 0);
	list = list->next;
	while (list)
	{
		key = get_key(list->content);
		printf("key: %s\n", key);
		value = get_value(list->content);
		printf("value: %s\n", value);
		check_env(key, value, env);
		free(key);
		free(value);
		list = list->next;
	}
	return (0);
}
