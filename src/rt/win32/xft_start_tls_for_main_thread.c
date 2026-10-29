/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_start_tls_for_main_thread.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 15:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 15:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/rt.h>

#ifdef _WIN32

__attribute__((const))
t_result	xft_start_tls_for_main_thread(t_sysinfo sysinfo)
{
	(void)sysinfo;
	return (OK);
}

#endif
