/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 21:11:00 by vgoyzuet          #+#    #+#             */
/*   Updated: 2024/12/27 21:48:16 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s3 = (char *)malloc((s1len + s2len) + 1);
	if (!s3)
		return (NULL);
	ft_memcpy(s3, s1, s1len);
	ft_memcpy(s3 + s1len, s2, s2len);
	s3[s1len + s2len] = '\0';
	return (s3);
}
