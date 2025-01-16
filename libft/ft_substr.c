/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 20:47:54 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/16 18:14:09 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen((char *)s);
	if (start >= slen)
		len = 0;
	else if ((start + len) > slen)
		len = slen - start;
	ss = malloc(sizeof(char *) + (len + 1));
	if (!ss)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		ss[i] = s[start + i];
		i++;
	}
	ss[i] = '\0';
	return (ss);
}
