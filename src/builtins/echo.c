/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:13:02 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/06 11:57:43 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(t_list *list)
{
	t_list	*tmp;
	char 	*joined;

	joined = NULL;
	tmp = list->next;
	while (tmp)
	{
		joined = ft_strjoin(joined, tmp->content);
		if (tmp->next)
			joined = ft_strjoin(joined, " ");
		tmp = tmp->next;
	}
	printf("%s\n", joined);
	free(joined);
}
