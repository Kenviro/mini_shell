/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:59:28 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/12 13:46:21 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	proper_exit(t_list *list, int status)
{
	ft_lstclear(&list);
	ft_putstr_fd("exit\n", 1);
	exit(status);
}

void	exit_shell(t_list *list)
{
	if (list->next)
	{
		if (ft_isdigit(((char *)list->next->content)[0]))
		{
			if (list->next->next)
			{
				ft_printf("exit\nminishell: exit: too many arguments\n");
				return ;
			}
			ft_printf("exit\n");
			proper_exit(list, ft_atoi(list->next->content));
		}
		else
		{
			ft_printf("exit\nminishell: exit: %s: numeric argument required\n", \
						list->next->content);
			proper_exit(list, 2);
		}
	}
	else
		proper_exit(list, EXIT_SUCCESS);
}
