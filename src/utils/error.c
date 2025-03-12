/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:05:04 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/12 11:25:36 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error(char *message)
{
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	new_line(char *input)
{
	free(input);
	rl_replace_line("", 0);
}

void	free_2d(char ***str)
{
	int	i;

	i = 0;
	while ((*str) && (*str)[i])
	{
		free((*str)[i]);
		i++;
	}
	free((*str));
	(*str) = NULL;
}

void	ft_envclear(t_env **l_env)
{
	t_env	*tmp;

	while (*l_env)
	{
		tmp = (*l_env)->next;
		free((*l_env)->key);
		(*l_env)->key = NULL;
		free((*l_env)->value);
		(*l_env)->value = NULL;
		free(*l_env);
		*l_env = tmp;
	}
	*l_env = NULL;
}

int	quote_cnf(char ***splited, int *ms_status)
{
	if ((*splited)[0][0] == '\0')
	{
		free_2d(splited);
		*ms_status = 127;
		printf("command not found :''\n");
		return (1);
	}
	return (0);
}
