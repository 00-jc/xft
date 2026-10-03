/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 14:01:38 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 14:07:17 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft.h>

__attribute__((__nonnull__(1), __noreturn__))
void	xft_main(const t_any *const __restrict__ sp)
{
	t_gpa			gpa;
	t_allocator		allocator;
	t_buffer		memory;

	(void)sp;
	gpa = xft_gpa();
	allocator = xft_gpa_allocator(&gpa);
	memory = allocator.vtable.allocate(allocator.allocator, 1000, 64);
	if (__builtin_expect(memory.mem == nullptr, 0))
	{
		allocator.vtable.destroy(allocator.allocator);
		xft_exit(1);
	}
	xft_pin_invariant(memory.size >= 1000);
	allocator.vtable.free(allocator.allocator, memory);
	xft_exit(0);
}
