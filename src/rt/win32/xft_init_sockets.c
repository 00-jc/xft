/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_init_sockets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 23:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 23:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/rt.h>

#ifdef _WIN32

# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>

t_result	xft_init_sockets(void)
{
	WSADATA	wsa;

	return ((t_result)(WSAStartup(MAKEWORD(2, 2), &wsa) == 0));
}

#endif
