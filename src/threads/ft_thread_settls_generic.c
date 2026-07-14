/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_settls_generic.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "private/ft_p_thread.h"

#if !defined(__i386__)

__attribute__((__always_inline__, unused, __nonnull__(2)))
inline t_uptr	ft__settls_arg(t_uptr tp, t_user_desc *__restrict__ const ud)
{
	(void)ud;
	return (tp);
}

#endif
