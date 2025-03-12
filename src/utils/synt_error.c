/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synt_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:26:01 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/12 11:36:52 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	synt_error(char *message, int *ms_status)
{
	ft_printf("syntax error near unexpected token '%s'\n", message);
	*ms_status = 2;
}

int	check_synt_error(t_list *list, int *ms_status)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
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
