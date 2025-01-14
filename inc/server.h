/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:26:35 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/14 20:03:05 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>

# define SIGNAL_RECEIVED SIGUSR2

typedef struct s_message
{
	int		size_message;
	char	*message;
}	t_msg;

typedef struct s_global
{
	int		client_pid;
	int		current_pid;
//	int		getting_header; ??
	int		getting_msg;
	t_msg	message;
}	t_global;

extern	t_global g_client;

//

#endif
