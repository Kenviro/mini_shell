/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:06:14 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/12 10:37:45 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_built_in(t_list *list)
{
	if (ft_strncmp(list->content, "echo", ft_strlen(list->content)) == 0)
	{
		echo(list);
		return (1);
	}
	else if (ft_strncmp(list->content, "exit", ft_strlen(list->content)) == 0)
		exit_shell(list);
	else if (ft_strncmp(list->content, "pwd", ft_strlen(list->content)) == 0)
	{
		pwd();
		return (1);
	}
	else if (ft_strncmp(list->content, "cd", ft_strlen(list->content)) == 0)
	{
		if (list->next)
			cd(list->next->content);
		else
			cd(NULL);
		return (1);
	}
	return (0);
}
