/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:25:00 by ktintim-          #+#    #+#             */
/*   Updated: 2024/10/03 17:25:04 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*subloop(char const *s, unsigned int start, size_t len, char *end)
{
	unsigned int	i;
	size_t			j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
		{
			end[j] = s[i];
			j++;
		}
		i++;
	}
	end[j] = '\0';
	return (end);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*end;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start >= i)
	{
		end = (char *)malloc(1);
		if (end)
			end[0] = '\0';
		return (end);
	}
	if (len > i - start)
		len = i - start;
	end = (char *)malloc((len + 1) * sizeof(char));
	if (!end)
		return (NULL);
	end = subloop(s, start, len, end);
	return (end);
}
