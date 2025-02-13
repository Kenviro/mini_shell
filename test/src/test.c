/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:36:21 by psoulie           #+#    #+#             */
/*   Updated: 2025/02/13 10:44:39 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_list *stuff;
	t_list *save;
	int i = 1;

	av = ft_split(av[1], ' ');
	(void)ac;
	stuff = ft_lstnew(av[0]);
	save = stuff;
	while (av[i])
	{
		stuff->next = ft_lstnew(av[i]);
		stuff = stuff->next;
		i++;
	}
	conditioning(save, env);
}
