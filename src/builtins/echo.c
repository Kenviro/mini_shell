/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:02 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/06 13:31:40 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_echo_arg(t_list *list)
{
	int		i;

	i = 1;
	if (list->content[0] == '-')
	{
		while (list->content[i] == 'n')
			i++;
		if (list->content[i] == '\0')
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
	tmp = list->next;
	while (tmp->next && check_echo_arg(tmp))
	{
		tmp = tmp->next;
		n_arg = 1;
	}
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
