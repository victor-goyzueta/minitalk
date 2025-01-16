/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:29:24 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/16 19:49:51 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	main(int argc, char **argv)
{
	t_info	client;
	int		size_message;

	if (argc == 3 && is_validate_pid(ft_itoa(arg[1])))
	{
		//
	}
	else
	{
		ft_printf("Invalid argument");
		exit(EXIT_FAILURE);
	}
	return (0);
}
