/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:53:23 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/25 15:28:49 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1 && s2)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (-1);
}

/* int main()
{
	char s1[] = "abcdef";
	char s2[] = "abc\375xx";
	printf("%d\n", ft_strncmp(s1, s2, 5));
} */

char	**ft_strdup_2d(char **str)
{
	int		i;
	char	**new_str;

	i = 0;
	while (str[i])
		i++;
	new_str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = ft_strdup(str[i]);
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}

void	check_fds(t_cmds *cmds, char **env, int *ms_status)
{
	t_cmds	*save;

	save = cmds;
	while (cmds)
	{
		if (cmds->fds[0] == -1)
		{
			free_stuff(save);
			ft_printf("Invalid file\n");
			*ms_status = main(-1, NULL, env);
			exit(*ms_status);
		}
		cmds = cmds->next;
	}
}
