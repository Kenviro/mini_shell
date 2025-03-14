/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:59:28 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/14 09:52:45 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	proper_exit(t_list *list, int status, char ***env)
{
	ft_lstclear(&list);
	free_2d(env);
	ft_putstr_fd("exit\n", 1);
	exit(status);
}

void	exit_shell(t_list *list, char ***env, int status)
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
			proper_exit(list, ft_atoi(list->next->content), env);
		}
		else
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", \
						list->next->content);
			proper_exit(list, 2, env);
		}
	}
	else
		proper_exit(list, status, env);
}
