/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:47:37 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/15 19:42:04 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_global	g_client;

// int	lost_signal(int s_si_pid, int signum, int *i, void *unused)
// {
// 	(void)unused;
// 	if (s_si_pid == 0 && (signum == SIGUSR1 || signum == SIGUSR2))
// 	{
// 		ft_printf_fd(1, "i: [%d] client: %d with signal: %d\n",
// 			(*i), s_si_pid, signum);
// 		s_si_pid = g_client.current_pid;
// 	}
// 	return (s_si_pid);
// }

int	get_signal_bit(int signum)
{
	if (signum == SIGUSR1)
		return (0);
	return (1);
}

void	header_handler(int *i, int signum)
{
	static int	bit_value;

	bit_value = get_signal_bit(signum);
	if ((*i) < 32)
	{
		g_client.message.size_message |= (bit_value << (31 - (*i)));
		(*i)++;
	}
	if ((*i) == 32)
	{
		ft_printf_fd(1, "MESSAGE SIZE: [%d]\n", g_client.message.size_message);
		g_client.message.message = malloc((g_client.message.size_message + 1) * 1);
		if (!g_client.message.message)
		{
			ft_printf_fd("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		g_client.getting_header = 0;
		g_client.getting_msg = 1;
		(*i) = 0;
	}
}

void	message_handler(int *i, int signum)
{
	static int	bit_value;
	static int	char_value;
	static int	message_pos;
	
	bit_value = get_signal_bit(signum);
	if (*i % 8 < 8)
	{
		char_value |= (bit_value << (7 - (*i % 8)));
		(*i)++;
	}
	if (*i % 8 == 0)
	{
		g_client.message.message[message_pos] = char_value;
		char_value = 0;
		message_pos++;
	}
	if (*i % 8 == g_client.message.size_message)
	{
		ft_printf_fd(1, "message: [%s]\n", g_client.message.message);
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
	info->si_pid = g_client.current_pid;
	if (info->si_pid == getpid())
	{
		ft_printf_fd(1, "Own process\n");
		exit(EXIT_FAILURE);
	}
	g_client.client_pid = info->si_pid;
	if (g_client.current_pid == 0)
	{
		kill(g_client.client_pid, SERVER_READY);
		g_client.current_pid = g_client.client_pid;
		g_client.getting_header = 1;
		return ;
	}
	else if (g_client.current_pid != g_client.client_pid)
		return ;
	if (g_client.getting_header == 1)
		header_handler(&i, signum);
	else if (g_client.getting_msg == 1)
		message_handler(&i, signum);
	if (g_client.client_pid != 0 && (signum == SIGUSR1 || signum == SIGUSR2))
		kill(g_client.client_pid, SIGNAL_RECEIVED);
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				server_pid;

	ft_memset(&g_client, 0, sizeof(t_global));
	server_pid = getpid();
	ft_printf_fd(1, "Server PID: %d\n", server_pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		sleep(1);
	}
	return (0);
}
