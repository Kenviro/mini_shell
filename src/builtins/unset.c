/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:22:44 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/21 14:04:05 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_remove_str(char **env, int i)
{
	char	**new_env;
	int		j;

	j = 0;
	while (env[j])
		j++;
	new_env = (char **)malloc(sizeof(char *) * j);
	if (!new_env)
		error("Malloc failed");
	j = 0;
	while (new_env[j])
	{
		if (j != i)
			new_env[j] = ft_strdup(env[j]);
		else
			j++;
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

static void	check_env(char *cmd, char **env)
{
	int	i;

	while (env[i])
	{
		if (ft_strcmp(env[i], cmd) == 0)
		{
			env = ft_remove_str(env, i);
			return ;
		}
		i++;
	}
}

void	unset(char **cmd, char **env)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
	{
		ft_printf("unset: not enough arguments\n");
		return ;
	}
	while (cmd[i])
	{
		check_env(cmd[i], env);
		i++;
	}
}
