/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:39:15 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/14 14:27:01 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_pwd(void)
{
	char	*path;
	char	*joined;

	path = getcwd(NULL, 0);
	joined = ft_strjoin(path, "$ :3 ");
	free (path);
	return (joined);
}

char	*executable(char *str)
{
	int		i;
	int		j;
	char	*exe;

	i = 0;
	while (str && str[i])
		i++;
	exe = malloc((i - 1) * sizeof(char));
	i = 3;
	j = 0;
	while (str && str[i])
	{
		exe[j] = str[i];
		i++;
		j++;
	}
	return (exe);
}

int	find_other(char **cmds)
{
	if (ft_strcmp(cmds[0], "cd") == 0 || \
		ft_strcmp(cmds[0], "exit") == 0 || \
		ft_strcmp(cmds[0], "unset") == 0 || \
		(ft_strcmp(cmds[0], "export") == 0 && cmds[1]))
		return (1);
	return (0);
}
