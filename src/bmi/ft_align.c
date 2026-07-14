/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_align.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 17:51:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 17:52:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

__attribute__((const, __always_inline__))
t_u64a	ft_align_fwd_integer(t_u64a qw, const t_u64a align)
{
	return (((qw + align) & ~align));
}

__attribute__((const, __always_inline__))
t_u64a	ft_align_bwd_integer(t_u64a qw, const t_u64a align)
{
	return ((qw & ~align));
}
