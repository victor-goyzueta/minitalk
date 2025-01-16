/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:38:17 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/16 19:48:29 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	is_validate_pid(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0)
		i++;
	}
	return (1);
}
