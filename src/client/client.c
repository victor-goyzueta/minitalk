/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:38:17 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/18 05:01:53 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_global g_server;

void	server_signal_handler(int signum, siginfo_t *info, void *unused)
{
	(void)unused;
	if (info->si_pid == getpid())
		ft_perror("Own process");
	if (info->si_pid != g_server.pid)
	{
		ft_printf_fd(2, "Unexpected sending process ID");
		return ;
	}
	if (signum == SERVER_READY)
		g_server.is_ready = 1;
	if (signum == SERVER_BUSY)
		g_server.is_ready = 0;
}

void	send_signal(pid_t server_pid, int signal)
{
	if (kill(server_pid, signal))
		ft_perror("Signal sending failed.");
}

void send_message_bits(t_info *client, size_t bits)
{
	unsigned long long	value;
	int					i;

	if (bits == 8)
		value = *((unsigned char *)client->size_message);
	if (bits == 32)
		value = *((unsigned int *)client->size_message);
	i = 32 - 1;
	while (i >= 0)
	{
		if (value & (1ULL << i))
			send_signal(client->server_pid, CHAR_1);
		else
			send_signal(client->server_pid, CHAR_0);
		i--;
		usleep(500 * 500);
	}
}

void client_signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)signum, (void)info, (void)context;
}

void	display_message(char *message, t_info *client)
{
	struct sigaction	sa;
	int					i;
	
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = client_signal_handler;
	sigaction(SIGUSR2, &sa, NULL);
	i = 0;
	while (message[i])
		send_message_bits(client, 8);
}
