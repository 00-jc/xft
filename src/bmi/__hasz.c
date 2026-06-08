/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __hasz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 04:05:57 by jaicastr          #+#    #+#             */
/*   Updated: 2026/02/20 19:20:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "private/ft_p_asm.h"

__attribute__((__always_inline__))
inline t_u64	ft_hasz64(t_u64 x)
{
	return (((x)-LONES_64) & (~x) & HIGHS_64);
}
