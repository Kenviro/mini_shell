/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:22:44 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/24 15:43:01 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **create_new_env(char **env)
{
	int	n;

	n = 0;
	while (env[n])
		n++;
	return ((char **)malloc(sizeof(char *) * n));
}

static char	**ft_remove_str(char **env, int index_to_remove)
{
	char	**new_env;
	int		i_env;
	int		i_new;

	new_env = create_new_env(env);
	if (!new_env)
		error("Malloc failed");
	i_env = 0;
	i_new = 0;
	while (env[i_env])
	{
		if (i_env == index_to_remove)
		{
			i_env++;
			continue ;
		}
		new_env[i_new] = ft_strdup(env[i_env]);
		i_new++;
		i_env++;
	}
	new_env[i_new] = NULL;
	free(env);
	return (new_env);
}

static void	check_env(t_list *list, char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], list->content, ft_strlen(list->content)) == 0)
		{
			*env = ft_remove_str((*env), i);
			printf("env = %s\n", (*env)[i]);
			return ;
		}
		i++;
	}
}

void	unset(t_list *list, char ***env)
{
	if (!list->next)
	{
		ft_printf("unset: not enough arguments\n");
		return ;
	}
	list = list->next;
	while (list)
	{
		check_env(list, env);
		list = list->next;
	}
}
