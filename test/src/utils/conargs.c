/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:55:44 by psoulie           #+#    #+#             */
/*   Updated: 2025/02/13 15:01:21 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_nbargs(t_list *lst)
{
	int	i;

	i = 0;
	while (lst && lst->content[0] != '|')
	{
		if (lst->content[0] == '<' || lst->content[0] == '>')
		{
			lst = lst->next;
			if (lst)
				lst = lst->next;
			continue ;
		}
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**red_init(void)
{
	char	**red;

	red = (char **)malloc(2 * sizeof(char *));
	red[0] = NULL;
	red[1] = NULL;
	return (red);
}

char	**set_args(t_list *lst, int nbargs, int icmd)
{
	int		i;
	char	**args;

	i = 0;
	args = (char **)malloc((nbargs + 1) * sizeof(char *));
	while (icmd)
	{
		if (lst->content[0] == '|')
			icmd--;
		lst = lst->next;
	}
	while (i < nbargs)
	{
		if (lst->content[0] == '>' || lst->content[0] == '<')
		{
			lst = lst->next;
			if (lst)
				lst = lst->next;
			continue ;
		}
		args[i++] = lst->content;
		lst = lst->next;
	}
	args[i] = NULL;
	return (args);
}
