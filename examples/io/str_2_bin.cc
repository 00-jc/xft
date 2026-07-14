/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_2_bin.cc                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/11 21:33:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft.hpp"

/*
 *	This program gets the first argument passed to it
 *	and converts the string of said argument into a binary
 *	string, and prints it to stdout.
 */

__attribute__((hot, nonnull(1), __always_inline__))
inline void	ft_fillb(t_u8 *__restrict__ const bytereprs, t_u8 const c)
{
	bytereprs[0] = (t_u8)xft::bmi::tern((c & (1 << 7)) != 0, '1', '0');
	bytereprs[1] = (t_u8)xft::bmi::tern((c & (1 << 6)) != 0, '1', '0');
	bytereprs[2] = (t_u8)xft::bmi::tern((c & (1 << 5)) != 0, '1', '0');
	bytereprs[3] = (t_u8)xft::bmi::tern((c & (1 << 4)) != 0, '1', '0');
	bytereprs[4] = (t_u8)xft::bmi::tern((c & (1 << 3)) != 0, '1', '0');
	bytereprs[5] = (t_u8)xft::bmi::tern((c & (1 << 2)) != 0, '1', '0');
	bytereprs[6] = (t_u8)xft::bmi::tern((c & (1 << 1)) != 0, '1', '0');
	bytereprs[7] = (t_u8)xft::bmi::tern((c & (1 << 0)) != 0, '1', '0');
}

extern "C"
{

__attribute__((__always_inline__, used))
inline int	ft_main(const xft::c::t_xft_rt *__restrict__ const rt)
{
	t_size						len;
	const t_u8					*arg;
	t_u8						c;
	xft::io::Writer				w;
	t_u8						bytereprs[8];
	t_u8						x[1024];

	if (__builtin_expect(rt->argc != 2, 0))
		return (1);
	if ((t_any)rt->argv == nullptr || rt->argv[1] == nullptr)
		__builtin_unreachable();
	arg = rt->argv[1];
	len = xft::cstr::strlen(reinterpret_cast<const char *>(arg));
	w = xft::io::Writer::fs(xft::mem::Buffer::fatptr(x, 1024).raw(),
			xft::io::get_stdout());
	while (len-- > 0)
	{
		c = *arg++;
		ft_fillb(bytereprs, c);
		w.write(xft::mem::Buffer::fatptr(bytereprs, 8).raw());
	}
	w.write(xft::mem::Buffer::fatptr(
			reinterpret_cast<const t_u8 *>("\n"), 1).raw());
	return ((void)w.flush(), 0);
}

}
