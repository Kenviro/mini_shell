/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:58:49 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/27 11:48:24 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static char	**ft_realloc_env(char **env, int size)
// {
// 	char	**new_env;
// 	int		i;

// 	i = 0;
// 	new_env = (char **)malloc(sizeof(char *) * size);
// 	if (!new_env)
// 		error("Malloc failed");
// 	while (env[i])
// 	{
// 		new_env[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	new_env[i] = NULL;
// 	free(env);
// 	return (new_env);
// }

// static char	*get_velue(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	*value;

// 	i = 0;
// 	while (str[i] && str[i] != '"')
// 		i++;
// 	if (str[i] == '\0')
// 		return (NULL);
// 	value = malloc(sizeof(char) * (ft_strlen(str) - i));
// 	if (!value)
// 		error("Malloc failed");
// 	i++;
// 	j = 0;
// 	while(str[i + 1])
// 	{
// 		value[j] = str[i];
// 		i++;
// 		j++;
// 	}
// 	return (value);
// }

// static char	*get_key(char *str)
// {
// 	int		i;
// 	char	*key;

// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 		i++;
// 	key = (char *)malloc(sizeof(char) * (i + 1));
// 	if (!key)
// 		error("Malloc failed");
// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 	{
// 		key[i] = str[i];
// 		i++;
// 	}
// 	key[i] = '\0';
// 	return (key);
// }

// static void	check_env(char *key, char *value, char **env)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0 && 
// 				env[i][ft_strlen(key)] == '=')
// 		{
// 			free(env[i]);
// 			tmp = ft_strjoin(key, "=");
// 			tmp = ft_strjoin(tmp, '"');
// 			tmp = ft_strjoin(tmp, value);
// 			tmp = ft_strjoin(tmp, '"');
// 			env[i] = ft_strdup(tmp);
// 			printf("exported %s\n", env[i]);
// 			free(tmp);
// 		}
// 	}
// 	env = ft_realloc_env(env, i + 2);
// 	env[i] = ft_strdup(cmd[i]);
// 	env[i + 1] = NULL;
// }

int	export(char **cmd, char **env)
{
	// char	*key;
	// char	*value;
	// int		i;

	// i = 1;
	if (cmd[1] == NULL)
		return (print_export(env), 0);
	// while (cmd[i])
	// {
	// 	key = get_key(cmd[i]);
	// 	value = get_value(cmd[i]);
	// 	check_env(key, value, env);
	// 	free(key);
	// 	free(value);
	// 	i++;
	// }
	return (0);
}
