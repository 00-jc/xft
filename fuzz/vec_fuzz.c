/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_fuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:15 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 13:33:41 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuzz.h"

static t_size	fuzz_vec_len(t_buffer *b)
{
	t_size	n;

	n = b->size / sizeof(int);
	if (n > FUZZ_VEC_CAP)
		n = FUZZ_VEC_CAP;
	return (n);
}

static void	fuzz_vec_case(t_fuzzer *fz, t_allocator alloc)
{
	t_buffer	*b;
	t_vec		v;
	t_size		n;
	int			last;

	b = xft_fuzz_get_rand(fz);
	n = fuzz_vec_len(b);
	v = xft_vec(alloc, 1, sizeof(int));
	xft_pin_invariant(v.buf.mem != nullptr);
	xft_pin_invariant(xft_vec_extend(alloc, &v,
			(t_buffer){.mem = b->mem, .size = n * sizeof(int)}));
	xft_pin_invariant(xft_vec_len(&v, sizeof(int)) == n);
	if (n != 0)
	{
		xft_memcpy(&last, b->mem + (n - 1) * sizeof(int), sizeof(int));
		xft_pin_invariant(xft_vec_popmv(&v, &last, sizeof(int)));
		xft_pin_invariant(xft_vec_len(&v, sizeof(int)) == n - 1);
	}
	xft_vec_destroy(alloc, &v);
}

void	xft_main(const t_any *__restrict__ const sp)
{
	t_fuzzer	fz;
	t_allocator	alloc;
	t_size		i;
	t_size		n;

	(void)sp;
	fz = xft_fuzzer_new(xft_new_arena_alloc());
	xft_pin_invariant(fz.arena.current != nullptr);
	xft_pin_invariant(xft_fuzzer_add_rand(&fz));
	alloc = xft_new_page_alloc();
	n = fz.buf_n * 2;
	i = 0;
	while (i++ < n)
		fuzz_vec_case(&fz, alloc);
	xft_fuzzer_destroy(&fz);
	xft_exit(0);
}
