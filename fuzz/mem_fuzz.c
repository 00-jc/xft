/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_fuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:01:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuzz.h"

static void	fuzz_mem_rw(t_fuzzer *fz)
{
	t_buffer	*a;
	t_u8		x[FUZZ_MEM_CAP + 1];
	t_u8		y[FUZZ_MEM_CAP + 1];
	size_t		n;

	a = ft_fuzz_get_rand(fz);
	ft_printf("trying mem size %lu alignment to word %lu\n", a->size,
		(t_uptr)a->mem & -(t_uptr)a->mem);
	n = a->size;
	ft_memcpy(x, a->mem, n);
	memcpy(y, a->mem, n);
	if (n > 1)
	{
		ft_memmove(x + 1, x, n - 1);
		memmove(y + 1, y, n - 1);
	}
	ft_pin_invariant(!memcmp(x, y, n));
}

static void	fuzz_mem_scan(t_fuzzer *fz)
{
	t_buffer	*a;
	t_buffer	*b;
	size_t		n;
	t_u8		c;

	a = ft_fuzz_get_rand(fz);
	b = ft_fuzz_get_rand(fz);
	n = a->size;
	if (b->size < n)
		n = b->size;
	c = ((t_u8 *)b->mem)[0];
	ft_pin_invariant(ft_memchr(a->mem, c, a->size)
		== memchr(a->mem, c, a->size));
	ft_pin_invariant(((ft_memcmp(a->mem, b->mem, n) > 0)
			- (ft_memcmp(a->mem, b->mem, n) < 0))
		== ((memcmp(a->mem, b->mem, n) > 0)
			- (memcmp(a->mem, b->mem, n) < 0)));
}

static void	fuzz_mem_fill(t_fuzzer *fz)
{
	t_buffer	*a;
	t_u8		x[FUZZ_MEM_CAP];
	t_u8		c;

	a = ft_fuzz_get_rand(fz);
	c = ((t_u8 *)a->mem)[0];
	ft_memcpy(x, a->mem, a->size);
	ft_memset(x, c, a->size);
	ft_pin_invariant(ft_memchr(x, c, a->size) == x);
	ft_bzero(x, a->size);
	ft_pin_invariant(x[0] == 0 && x[a->size - 1] == 0);
}

static void	fuzz_strlen_case(t_fuzzer *fz)
{
	t_buffer	*b;
	char		x[FUZZ_MEM_CAP + 1];
	size_t		i;
	size_t		n;

	b = ft_fuzz_get_rand(fz);
	i = 0;
	while (i < b->size)
	{
		x[i] = (((char *)b->mem)[i] | 1);
		++i;
	}
	n = ft_fuzz_get_rand_u(fz) % (b->size + 1);
	x[n] = 0;
	x[b->size] = 0;
	ft_pin_invariant(ft_strlen(x) == strlen(x));
}

int	main(void)
{
	t_fuzzer	fz;
	size_t		i;
	size_t		n;

	fz = ft_fuzzer_new(ft_new_arena_alloc());
	ft_pin_invariant(fz.arena.current != nullptr);
	ft_pin_invariant(ft_fuzzer_add_rand(&fz));
	n = fz.buf_n * 2;
	i = 0;
	while (i++ < n)
	{
		fuzz_mem_rw(&fz);
		fuzz_mem_scan(&fz);
		fuzz_mem_fill(&fz);
		fuzz_strlen_case(&fz);
	}
	ft_fuzzer_destroy(&fz);
	return (0);
}
