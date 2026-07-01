/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_fuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:15 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:51:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuzz.h"

static void	fuzz_mem_rw(t_fuzzer *fz)
{
	t_buffer	*a;
	t_u8		x[FUZZ_MEM_CAP + 1];
	t_u8		y[FUZZ_MEM_CAP + 1];
	t_size		n;

	a = ft_fuzz_get_rand(fz);
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
	t_size		n;
	t_u8		c;

	a = ft_fuzz_get_rand(fz);
	b = ft_fuzz_get_rand(fz);
	n = a->size;
	if (b->size < n)
		n = b->size;
	c = b->mem[0];
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
	c = a->mem[0];
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
	t_size		i;
	t_size		n;

	b = ft_fuzz_get_rand(fz);
	i = 0;
	while (i < b->size)
	{
		x[i] = (b->mem[i] | 1);
		++i;
	}
	n = ft_fuzz_get_rand_u(fz) % (b->size + 1);
	x[n] = 0;
	x[b->size] = 0;
	ft_pin_invariant(ft_strlen(x) == strlen(x));
}

int	ft_main(t_size argc, t_u8 **argv, t_u8 **envp)
{
	t_fuzzer	fz;
	t_size		i;
	t_size		n;

	(void)argc;
	(void)argv;
	(void)envp;
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
