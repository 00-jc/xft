/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_fuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:01:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/14 07:38:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuzz.h"

static size_t	fuzz_vec_len(t_buffer *b)
{
	size_t	n;

	n = b->size / sizeof(int);
	if (n > FUZZ_VEC_CAP)
		n = FUZZ_VEC_CAP;
	return (n);
}

static void	fuzz_vec_case(t_fuzzer *fz, t_allocator alloc)
{
	t_buffer	*b;
	t_vec		v;
	size_t		n;
	int			last;

	b = ft_fuzz_get_rand(fz);
	n = fuzz_vec_len(b);
	v = ft_vec(alloc, 1, sizeof(int));
	ft_pin_invariant(v.buf.mem != nullptr);
	ft_pin_invariant(ft_vec_extend(alloc, &v,
			(t_buffer){.mem = b->mem, .size = n * sizeof(int)}, sizeof(int)));
	ft_printf("vec extend + copy test: size=%lu, capacity=%lu\n", v.size,
		v.capacity);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == n);
	if (n != 0)
	{
		ft_memcpy(&last, b->mem + (n - 1) * sizeof(int), sizeof(int));
		ft_pin_invariant(ft_vec_popmv(&v, &last, sizeof(int)));
		ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == n - 1);
	}
	ft_vec_destroy(alloc, &v);
}

int	main(void)
{
	t_fuzzer	fz;
	t_allocator	alloc;
	size_t		i;
	size_t		n;

	fz = ft_fuzzer_new(ft_new_arena_alloc());
	ft_pin_invariant(fz.arena.current != nullptr);
	ft_pin_invariant(ft_fuzzer_add_rand(&fz));
	alloc = ft_new_page_alloc();
	n = fz.buf_n * 2;
	i = 0;
	while (i++ < n)
		fuzz_vec_case(&fz, alloc);
	ft_fuzzer_destroy(&fz);
	return (0);
}
