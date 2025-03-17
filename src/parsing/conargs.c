/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:55:44 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/17 13:40:08 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	next_cmd(t_list **firstlist)
{
	t_list	*lst;

	lst = *firstlist;
	while (lst && lst->content[0] != '|')
		lst = lst->next;
	if (lst && lst->content[0] == '|')
		lst = lst->next;
	*firstlist = lst;
}

int	count_cmds(t_list *lst)
{
	int	i;

	i = 0;
	if (lst)
		i++;
	while (lst && lst->content)
	{
		if (lst->content[0] == '|' && lst->next)
			i++;
		lst = lst->next;
	}
	return (i);
}

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

char	**set_args(t_list *lst, int nbargs)
{
	int		i;
	char	**args;

	i = 0;
	args = (char **)malloc((nbargs + 1) * sizeof(char *));
	while (i < nbargs)
	{
		if (lst->content[0] == '>' || lst->content[0] == '<')
		{
			lst = lst->next;
			if (lst)
				lst = lst->next;
			continue ;
		}
		else
			args[i++] = ft_strdup(lst->content);
		lst = lst->next;
	}
	args[i] = NULL;
	return (args);
}

char	**find_args(t_list *lst)
{
	int		nbargs;
	char	**args;

	nbargs = find_nbargs(lst);
	args = set_args(lst, nbargs);
	return (args);
}
