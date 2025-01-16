/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:25:06 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/16 19:46:51 by vgoyzuet         ###   ########.fr       */
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

//

# define CHAR_0 SIGUSR1
# define CHAR_1 SIGUSR2

typedef struct s_data
{
	pid_t	client_pid;
	pid_t	server_pid;
	char	*str;
}	t_info;

typedef struct s_global
{
	int						pid;
	volatile sig_atomic_t	is_ready;
}	t_global;

extern t_global	g_server;

int	is_validate_pid(char *str);

#endif
