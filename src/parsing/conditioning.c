/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditioning.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:18:24 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/06 18:19:00 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_cmds(t_list *lst)
{
	int	i;

	i = 0;
	while (lst && lst->content)
	{
		if (lst->content[0] == '>' || lst->content[0] == '<'
				|| lst->content[0] == '|')
			i -= 2;
		else if (lst->content[0] == '-')
			i--;
		lst = lst->next;
		i++;
	}
	return (i);
}

void	assign_redirection(char ***red, t_list *lst)
{
	if (lst->content[0] == '<')
	{
		if (*red[0])
			free(*red[0]);
		if (lst->content[1] == '<')
			*red[0] = ft_strjoin("<< ", lst->next->content);
		else
			*red[0] = ft_strjoin("< ", lst->next->content);
	}
	else
	{
		if (*red[1])
			free(*red[1]);
		if (lst->content[1] == '>')
			*red[1] = ft_strjoin(">> ", lst->next->content);
		else
			*red[1] = ft_strjoin("> ", lst->next->content);
	}
}

void	distribute(t_list *lst, char **cmds, char **red)
{
	int	i;

	i = 0;
	while (lst && lst->content)
	{
		if ((lst->content[0] == '>' || lst->content[0] == '<') && lst->next)
		{
			assign_redirection(&red, lst);
		}
		else if (lst->content[0] == '-')
			i--;
		lst = lst->next;
		i++;
	}
}

void	conditioning(t_list *lst)
{
	t_list	*iter;
	char	**cmds;
	char	*red[2];
	int		nbcmds;
	int		i;

	i = 0;
	iter = lst;
	red[0] = NULL;
	red[1] = NULL;
	nbcmds = count_cmds(iter);
	cmds = (char **)malloc((nbcmds + 1) * sizeof (char *));
	distribute(iter, cmds, red);
}
