/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditioning.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:18:24 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/19 12:59:28 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**find_args(t_list *lst, int icmd)
{
	int		nbargs;
	char	**args;

	nbargs = find_nbargs(lst);
	args = (char **)malloc((nbargs + 1) * sizeof(char *));
	args = set_args(lst, nbargs, icmd);
	return (args);
}

static int	count_cmds(t_list *lst)
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

char	**assign_redirection(char **red, t_list *lst)
{
	if (lst->content[0] == '<')
	{
		if (red[0])
			free(red[0]);
		if (lst->content[1] == '<')
			red[0] = ft_strjoin("<< ", lst->next->content);
		else
			red[0] = ft_strjoin("< ", lst->next->content);
	}
	else
	{
		if (red[1])
			free(red[1]);
		if (lst->content[1] == '>')
			red[1] = ft_strjoin(">> ", lst->next->content);
		else
			red[1] = ft_strjoin("> ", lst->next->content);
	}
	return (red);
}

void	distribute(t_list *lst, char ***cmds, char **red, char **env)
{
	int	i;

	i = 0;
	while (lst && lst->content)
	{
		if ((lst->content[0] == '>' || lst->content[0] == '<') && lst->next)
			red = assign_redirection(red, lst);
		lst = lst->next;
		i++;
	}
	command(cmds, red, env);
}

void	conditioning(t_list *lst, char **env)
{
	t_list	*iter;
	char	***cmds;
	char	**red;
	int		nbcmds;
	int		i;
	
	iter = lst;
	red = red_init();
	nbcmds = count_cmds(iter);
	cmds = (char ***)malloc((nbcmds + 1) * sizeof(char **));
	i = 0;
	while (nbcmds--)
	{
		cmds[i] = find_args(lst, i);
		i++;
	}
	distribute(iter, cmds, red, env);
}
