/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:29:24 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/21 17:10:27 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	is_validate_pid(char *server_pid)
{
	int	i;

	i = 0;
	if (!server_pid[i])
		return (0);
	while (server_pid[i])
	{
		if (!ft_isdigit(server_pid[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_server_ready(int server_pid)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_signal_handler;
	g_server.pid = server_pid;
	g_server.is_ready = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		kill(server_pid, REQUEST_REPLY);
		ft_printf("Waiting server response...\n");
		sleep(1);
		if (g_server.is_ready == 1)
			break ;
	}
	ft_printf("Server ready: (%d)\n", g_server.is_ready);
	return (g_server.is_ready);
}

void	init_client_data(char **argv, t_info *client)
{
	ft_memset(client, 0, sizeof(t_info));
	client->server_pid = ft_atoi_limitis(argv[1]);
	client->client_pid = getpid();
	ft_printf("Client PID: %d\n", client->client_pid);
	client->message = argv[2];
	if (client->server_pid == 0)
		ft_perror("Signal sending failed.");
}

int	main(int argc, char **argv)
{
	t_info	client;
	int		len;

	ft_printf("Number of arguments: %d\n", argc - 1);
	if (argc == 3 && is_validate_pid(argv[1]))
	{
		init_client_data(argv, &client);
		len = ft_strlen(argv[2]);
		if (is_server_ready(client.server_pid))
		{
			ft_printf("Message lenght [%d]\n", len);
			send_message_bits(&len, &client, 32);
			display_message(client.message, &client);
		}
	}
	else
		ft_perror("Invalid arguments");
	return (0);
}
