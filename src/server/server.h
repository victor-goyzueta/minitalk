/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:26:35 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/22 21:05:07 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/time.h>

# define SERVER_READY SIGUSR1

# define SIGNAL_RECEIVED SIGUSR2

# define BYTE 8
# define BYTE_4 32

typedef struct s_message
{
	int		size_message;
	char	*message;
}	t_msg;

typedef struct s_global
{
	pid_t		client_pid;
	pid_t		current_pid;
	int			getting_header;
	int			getting_msg;
	t_msg		message;
}	t_global;

extern t_global	g_client;

int		lost_signal(int s_si_pid, int signum);
int		get_signal_bit(int signum);
void	header_handler(int *i, int signum);
void	message_handler(int *i, int signum);
void	server_signal_handler(int signum, siginfo_t *info, void *unused);

#endif
