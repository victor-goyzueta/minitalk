/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:25:06 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/22 21:05:07 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/time.h>

# define SERVER_READY SIGUSR1
# define SERVER_BUSY SIGUSR2

# define REQUEST_REPLY SIGUSR1
# define REF_SIGNAL SIGUSR2

# define CHAR_0 SIGUSR1
# define CHAR_1 SIGUSR2

# define BYTE 8
# define BYTE_4 32

typedef struct s_data
{
	pid_t	client_pid;
	pid_t	server_pid;
	char	*message;
}	t_info;

typedef struct s_global
{
	pid_t					pid;
	volatile sig_atomic_t	is_ready;
}	t_global;

extern t_global	g_server;

void	init_client_data(char **argv, t_info *client);
int		is_server_ready(int server_pid);
void	client_signal_handler(int signum, siginfo_t *info, void *unused);
void	send_message_bits(void *bytes, t_info *client, size_t bits);
void	send_signal(pid_t server_pid, int signal);
void	send_message_content(char *message, t_info *client);

#endif
