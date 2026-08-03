/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigfillset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:37:54 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 01:17:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "signals.h"

__attribute__((const, __always_inline__))
inline t_sigset	ft_sigfillset(void)
{
	t_sigset	set;

	ft_memset(&set, 0xff, sizeof(set));
	return (set);
}
