/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:10:43 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/20 17:49:09 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	main(void)
{
	struct sigaction	sa;
	pid_t				server_pid;

	ft_memset(&g_client, 0, sizeof(t_global));
	server_pid = getpid();
	ft_printf("Server PID: %d\n", server_pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		sleep(1);
	return (0);
}
