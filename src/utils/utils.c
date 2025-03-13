/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:39:15 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/13 17:33:34 by ktintim-         ###   ########.fr       */
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

int	is_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' || input[i] != '\t' || input[i] != '\v' || \
				input[i] != '\f' || input[i] != '\r')
			return (i);
		i++;
	}
	return (i);
}
