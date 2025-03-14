/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synt_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:26:01 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/14 16:55:25 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	synt_error(char *message, int *ms_status)
{
	ft_printf("syntax error near unexpected token '%s'\n", message);
	*ms_status = 2;
}

static int	double_and_solopipe(t_list *list, int *ms_status)
{
	if (list->content[0] == '|' && !list->next)
	{
		synt_error("|", ms_status);
		return (1);
	}
	if ((ft_strcmp(list->content, ">>") == 0 || \
		ft_strcmp(list->content, "<<") == 0) && !list->next)
	{
		synt_error("newline", ms_status);
		return (1);
	}
	if ((ft_strcmp(list->content, ">>") == 0 || \
		(ft_strcmp(list->content, "<<") == 0)) && \
		((ft_strcmp(list->next->content, ">>") == 0) || \
		(ft_strcmp(list->next->content, "<<") == 0) || \
		(ft_strcmp(list->content, ">") == 0) || \
		(ft_strcmp(list->content, "<") == 0) || \
		(ft_strcmp(list->content, "|") == 0)))
	{
		synt_error(list->next->content, ms_status);
		return (1);
	}
	return (0);
}

static int	at_start(t_list *list, int *ms_status)
{
	if (list->content[0] == '|' || list->content[0] == '>' || \
		list->content[0] == '<')
	{
		synt_error(list->content, ms_status);
		return (1);
	}
	return (0);
}

int	check_synt_error(t_list *list, int *ms_status)
{
	t_list	*tmp;

	tmp = list;
	if (at_start(tmp, ms_status))
		return (1);
	while (tmp)
	{
		if (double_and_solopipe(tmp, ms_status))
			return (1);
		if ((tmp->content[0] == '>' || tmp->content[0] == '<') && !tmp->next)
		{
			synt_error("newline", ms_status);
			return (1);
		}
		if ((tmp->content[0] == '>' || tmp->content[0] == '<' || \
			tmp->content[0] == '|') && (tmp->next->content[0] == '>' || \
			tmp->next->content[0] == '<' || tmp->next->content[0] == '|'))
		{
			synt_error(tmp->next->content, ms_status);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
