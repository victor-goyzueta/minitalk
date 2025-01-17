/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:29:24 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/17 21:36:13 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	main(int argc, char **argv)
{
	t_info	client;
	int		size_message;

	if (argc == 3 && is_validate_pid(ft_itoa(argv[1])))
	{
		init_client_data(argv, &client);
		//
	}
	else
		ft_perror("Invalid argument");
	return (0);
}
