/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 20:15:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/19 23:13:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fibhashc.h"

__attribute__((__noreturn__, __nonnull__(1)))
void	xft_main(const t_any *__restrict__ const sp)
{
	const t_kernel_ptrs	ptrs = xft_get_kernel_ptrs(sp);
	t_u8				stdout_buffer[1024];
	t_writer			stdout_w;
	t_buffer			src;
	t_gpa				gpa;

	if (__builtin_expect(ptrs.argc != 2, 0))
		xft_exit(1);
	stdout_w = xft_get_fs_writer(xft_fatptr(stdout_buffer, 1024),
			xft_get_stdout());
	(void)stdout_w;
	src = xft_map_file(ptrs.argv[1], O_RDONLY);
	if (__builtin_expect(src.mem == nullptr, 0))
		xft_exit(1);
	gpa = xft_new_gpa();
	if (__builtin_expect(gpa.slab == nullptr, 0))
		xft_exit(1);
	get_hash(xft_gpa_allocator(&gpa), &stdout_w, src);
	xft_gpa_destroy(&gpa);
	xft_unmap_file(src);
	xft_exit(0);
}
