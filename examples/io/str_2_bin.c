/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_2_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 22:11:31 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 11:41:11 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fmt.h"
#include "xft.h"
#include "private/ft_p_rt.h"

/*
 *	This program gets the first argument passed to it
 *	and converts the string of said argument into a binary
 *	string, and prints it to stdout. 
 */

__attribute__((hot, nonnull(1), __always_inline__))
inline void	ft_fillb(t_u8 *__restrict__ const bytereprs, t_u8 const c)
{
	bytereprs[0] = (t_u8)ft_tern((c & (1 << 7)) != 0, '1', '0');
	bytereprs[1] = (t_u8)ft_tern((c & (1 << 6)) != 0, '1', '0');
	bytereprs[2] = (t_u8)ft_tern((c & (1 << 5)) != 0, '1', '0');
	bytereprs[3] = (t_u8)ft_tern((c & (1 << 4)) != 0, '1', '0');
	bytereprs[4] = (t_u8)ft_tern((c & (1 << 3)) != 0, '1', '0');
	bytereprs[5] = (t_u8)ft_tern((c & (1 << 2)) != 0, '1', '0');
	bytereprs[6] = (t_u8)ft_tern((c & (1 << 1)) != 0, '1', '0');
	bytereprs[7] = (t_u8)ft_tern((c & (1 << 0)) != 0, '1', '0');
}

__attribute__((__always_inline__))
inline void	ft_main(const t_any *__restrict__ const sp)
{
	t_kernel_ptrs	kp;
	t_size			len;
	t_writer		w;
	t_u8			bytereprs[8];
	t_u8			x[1024];

	kp = ft_get_kernel_ptrs(sp);
	if (__builtin_expect(kp.argc != 2, 0))
		ft_exit(1);
	if ((t_any)kp.argv == nullptr || kp.argv[1] == nullptr)
		__builtin_unreachable();
	len = ft_strlen((const char *)kp.argv[1]);
	w = ft_get_fs_writer(ft_fatptr(x, 1024), ft_get_stdout());
	while (len-- > 0)
	{
		ft_fillb(bytereprs, *kp.argv[1]++);
		ft_writer_write(&w, ft_fatptr(bytereprs, 8));
	}
	ft_writer_write(&w, ft_fatptr((t_u8 *)"\n", 1));
	(void)ft_writer_flush(&w);
	ft_exit(0);
}
