/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pin_invariant.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 14:33:08 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_hint.h"

__attribute__((__always_inline__))
inline void	ft_pin_invariant(int res)
{
	if (!res)
		ft_hardcrash();
}

__attribute__((__always_inline__))
inline void	ft_pin_invariant_msg(int res, t_buffer msg)
{
	if (!res)
		ft_hardcrash_with_message(msg);
}
