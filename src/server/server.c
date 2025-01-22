/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:47:37 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/22 20:42:55 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_global	g_client;

int	lost_signal(int s_si_pid, int signum)
{
	static int	last_pid;

	if (s_si_pid == 0 && (signum == SIGUSR1 || signum == SIGUSR2))
		s_si_pid = g_client.current_pid;
	if (last_pid != s_si_pid && s_si_pid == g_client.current_pid)
	{
		ft_printf("\nClient PID: %d\n", s_si_pid);
		last_pid = s_si_pid;
	}
	return (s_si_pid);
}

int	get_signal_bit(int signum)
{
	if (signum == SIGUSR1)
		return (0);
	return (1);
}

void	header_handler(int *i, int signum)
{
	const int	bit_value = get_signal_bit(signum);

	if ((*i) < BYTE_4)
	{
		g_client.message.size_message |= (bit_value << (BYTE_4 - 1 - (*i)));
		(*i)++;
	}
	if ((*i) == BYTE_4)
	{
		ft_printf("Message size: [%d]\n", g_client.message.size_message);
		g_client.message.message = malloc((g_client.message.size_message + 1)
				* 1);
		if (!g_client.message.message)
			ft_perror("Memory allocation failed");
		g_client.getting_header = 0;
		g_client.getting_msg = 1;
		(*i) = 0;
	}
}

void	message_handler(int *i, int signum)
{
	const int	bit_value = get_signal_bit(signum);
	static int	char_value;
	static int	message_pos;

	if (*i % 8 < BYTE)
	{
		char_value |= (bit_value << (BYTE - 1 - (*i % 8)));
		(*i)++;
	}
	if (*i % 8 == 0)
	{
		g_client.message.message[message_pos] = char_value;
		char_value = 0;
		message_pos++;
	}
	if (*i / 8 == g_client.message.size_message)
	{
		ft_printf("Message content:\n%s\n", g_client.message.message);
		free(g_client.message.message);
		ft_bzero(&g_client, sizeof(g_client));
		g_client.getting_header = 1;
		(*i) = 0;
		message_pos = 0;
	}
}

void	server_signal_handler(int signum, siginfo_t *info, void *unused)
{
	static int	i;

	(void)unused;
	info->si_pid = lost_signal(info->si_pid, signum);
	if (info->si_pid == getpid())
		ft_perror("Own process\n");
	g_client.client_pid = info->si_pid;
	if (g_client.current_pid == 0)
	{
		kill(g_client.client_pid, SERVER_READY);
		g_client.current_pid = g_client.client_pid;
		g_client.getting_header = 1;
		return ;
	}
	if (g_client.current_pid != g_client.client_pid)
		return ;
	if (g_client.getting_header == 1)
		header_handler(&i, signum);
	else if (g_client.getting_msg == 1)
		message_handler(&i, signum);
	if (g_client.client_pid != 0 && (signum == SIGUSR1 || signum == SIGUSR2))
		kill(g_client.client_pid, SIGNAL_RECEIVED);
}
