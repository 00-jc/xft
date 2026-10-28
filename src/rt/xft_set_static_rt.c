/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_set_static_rt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/28 22:21:38 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/rt.h>
#include <xft/bmi.h>

__attribute__((__always_inline__, __used__))
inline const t_xft_rt	*xft_set_static_rt(
	const t_xft_rt *__restrict__ const rt)
{
	static const t_xft_rt	*__restrict__
		rt_static = nullptr;

	rt_static = (t_any)xft_tern(rt_static == nullptr, (t_uptr)rt, 0);
	return (rt_static);
}
