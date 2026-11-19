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

#ifdef __linux__

__attribute__((const))
t_result	xft_init_sockets(void)
{
	return ((t_result){.ok = OK});
}

#endif
