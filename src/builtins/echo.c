/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:02 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/06 13:16:36 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_echo_arg(t_list *list)
{
	t_list	*next;
	int		i;

	i = 1;
	next = list->next;
	if (next->content[0] == '-')
	{
		while (next->content[i] == 'n')
			i++;
		if (next->content[i] == '\0')
			return (1);
	}
	return (0);
}

void	echo(t_list *list)
{
	t_list	*tmp;
	int		n_arg;
	char	*joined;

	n_arg = 0;
	joined = NULL;
	if (list->next && check_echo_arg(list))
	{
		tmp = list->next->next;
		n_arg = 1;
	}
	else
		tmp = list->next;
	while (tmp)
	{
		joined = ft_strjoin(joined, tmp->content);
		if (tmp->next)
			joined = ft_strjoin(joined, " ");
		tmp = tmp->next;
	}
	if (!n_arg)
		printf("%s\n", joined);
	else
		printf("%s", joined);
	free(joined);
}
