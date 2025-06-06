/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditioning.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:18:24 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/26 12:51:36 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_nbcmds(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		cmds = cmds->next;
		i++;
	}
	return (i);
}

int	find_fdout(t_list *lst)
{
	int	fd;

	fd = 1;
	while (lst && lst->content[0] != '|')
	{
		if (lst->content[0] == '>')
		{
			if (fd != 1)
				close(fd);
			if (lst->content[1] == '>')
			{
				lst = lst->next;
				fd = open(lst->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
			else
			{
				lst = lst->next;
				fd = open(lst->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
		}
		lst = lst->next;
	}
	return (fd);
}

int	find_fdin(t_list *lst)
{
	int	fd;

	fd = 0;
	while (lst && lst->content[0] != '|')
	{
		if (lst->content[0] == '<')
		{
			if (fd != 0)
				close(fd);
			if (lst->content[1] != '<')
			{
				lst = lst->next;
				fd = open(lst->content, O_RDONLY);
			}
			else
			{
				lst = lst->next;
				fd = -20;
			}
		}
		lst = lst->next;
	}
	return (fd);
}

t_cmds	*new_cmd(t_list *lst)
{
	t_cmds	*cmds;

	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->next = NULL;
	cmds->cmd = find_args(lst);
	cmds->fds[0] = find_fdin(lst);
	cmds->fds[1] = find_fdout(lst);
	if (cmds->fds[0] == -20)
	{
		while (lst && lst->content[0] != '<' && lst->content[0] != '<')
			lst = lst->next;
		if (lst)
			lst = lst->next;
		cmds->limiter = ft_strdup(lst->content);
	}
	else
		cmds->limiter = NULL;
	return (cmds);
}

void	conditioning(t_list *lst, char **env, int *ms_status)
{
	t_cmds	*cmds;
	t_cmds	*save;
	t_list	*save_list;

	save_list = lst;
	cmds = new_cmd(lst);
	save = cmds;
	next_cmd(&lst);
	while (lst)
	{
		cmds->next = new_cmd(lst);
		cmds = cmds->next;
		next_cmd(&lst);
	}
	ft_lstclear(&save_list);
	command(save, env, ms_status);
}
