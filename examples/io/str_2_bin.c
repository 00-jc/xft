/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_2_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 22:11:31 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 16:38:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fmt.h"
#include "xft.h"
#include "xft_p_rt.h"

__attribute__((hot, __nonnull__(1), __always_inline__))
inline void	xft_fillb(t_u8 *__restrict__ const bytereprs, t_u8 const c)
{
	bytereprs[0] = (t_u8)xft_tern((c & (1 << 7)) != 0, '1', '0');
	bytereprs[1] = (t_u8)xft_tern((c & (1 << 6)) != 0, '1', '0');
	bytereprs[2] = (t_u8)xft_tern((c & (1 << 5)) != 0, '1', '0');
	bytereprs[3] = (t_u8)xft_tern((c & (1 << 4)) != 0, '1', '0');
	bytereprs[4] = (t_u8)xft_tern((c & (1 << 3)) != 0, '1', '0');
	bytereprs[5] = (t_u8)xft_tern((c & (1 << 2)) != 0, '1', '0');
	bytereprs[6] = (t_u8)xft_tern((c & (1 << 1)) != 0, '1', '0');
	bytereprs[7] = (t_u8)xft_tern((c & (1 << 0)) != 0, '1', '0');
}

__attribute__((__always_inline__))
inline void	xft_main(const t_any *__restrict__ const sp)
{
	t_kernel_ptrs	kp;
	const t_nat_str	*s;
	t_writer		w;
	t_u8			bytereprs[8];
	t_u8			x[1024];

	kp = xft_get_kernel_ptrs(sp);
	if (__builtin_expect(kp.argc != 2, 0))
		xft_exit(1);
	if ((t_any)kp.argv == nullptr || kp.argv[1] == nullptr)
		__builtin_unreachable();
	s = kp.argv[1];
	w = xft_get_fs_writer(xft_fatptr(x, 1024), xft_get_stdout());
	while (*s != '\0')
	{
		xft_fillb(bytereprs, (t_u8)(*s));
		s++;
		xft_writer_write(&w, xft_fatptr(bytereprs, 8));
	}
	xft_writer_write(&w, xft_fatptr((t_u8 *)"\n", 1));
	(void)xft_writer_flush(&w);
	xft_exit(0);
}
