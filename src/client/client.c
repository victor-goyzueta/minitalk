/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:38:17 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/24 15:49:57 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_global	g_server;

void	client_signal_handler(int signum, siginfo_t *info, void *unused)
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

void	send_message_bits(void *bytes, t_info *client, size_t bits)
{
	unsigned long long	value;
	int					i;

	value = 0;
	if (bits == BYTE)
		value = *((unsigned char *)bytes);
	else if (bits == BYTE_4)
		value = *((unsigned int *)bytes);
	i = bits - 1;
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

void	reference_signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)signum, (void)info, (void)context;
}

void	send_message_content(char *message, t_info *client)
{
	struct sigaction	sa;
	int					i;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = reference_signal_handler;
	sigaction(REF_SIGNAL, &sa, NULL);
	i = 0;
	while (message[i])
		send_message_bits(&message[i++], client, 8);
}
