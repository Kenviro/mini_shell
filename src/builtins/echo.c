/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:02 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/11 13:01:03 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_echo_arg(char *flag)
{
	int		i;

	i = 1;
	if (flag[0] == '-')
	{
		while (flag[i] == 'n')
			i++;
		if (flag[i] == '\0')
			return (1);
	}
	return (0);
}

static char	*create_joined(char **cmd, int i)
{
	char	*joined;

	joined = ft_strdup(cmd[i]);
	if (cmd[i + 1])
		joined = ft_strjoin(joined, " ");
	i++;
	while (cmd[i])
	{
		joined = ft_strjoin(joined, cmd[i]);
		if (cmd[i + 1])
			joined = ft_strjoin(joined, " ");
		i++;
	}
	return (joined);
}

void	echo(char **cmd)
{
	int		i;
	int		n_arg;
	char	*joined;

	i = 1;
	n_arg = 0;
	joined = NULL;
	while (cmd[i] && check_echo_arg(cmd[i]))
	{
		i++;
		n_arg = 1;
	}
	if (cmd[i])
	{
		joined = create_joined(cmd, i);
		if (!n_arg)
			printf("%s\n", joined);
		else
			printf("%s", joined);
		free(joined);
	}
	else
		printf("\n");
}
