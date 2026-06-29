/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"
#include "alloc.h"

static void	test_arena_basic(void);
static void	test_arena_alignment(void);
static void	test_arena_invalid(void);
static void	test_arena_checkpoint(void);

void	test_arena_basic(void)
{
	t_arena	a;
	t_u8	*buf;
	void	*prev;
	void	*p;
	int		i;

	a = ft_new_arena_alloc();
	ft_pin_invariant_msg(a.current != nullptr, (char *)"init");
	buf = ft_arena_alloc(&a, 4096, 16);
	ft_pin_invariant_msg(buf != nullptr, (char *)"alloc");
	i = -1;
	while (++i < 4096)
		buf[i] = (t_u8)(i * 31 + 7);
	i = -1;
	while (++i < 4096)
		ft_pin_invariant_msg(buf[i] == (t_u8)(i * 31 + 7), (char *)"rw");
	prev = buf;
	i = -1;
	while (++i < 5000)
	{
		p = ft_arena_alloc(&a, 64, 8);
		ft_pin_invariant_msg(p != nullptr && p != prev, (char *)"uniq");
		prev = p;
	}
	ft_destroy_arena(&a);
}

void	test_arena_alignment(void)
{
	t_arena	a;
	void	*p;
	t_size	aligns[7];
	t_size	i;

	aligns[0] = 1;
	aligns[1] = 2;
	aligns[2] = 4;
	aligns[3] = 8;
	aligns[4] = 16;
	aligns[5] = 32;
	aligns[6] = 64;
	a = ft_new_arena_alloc();
	i = -1;
	while (++i < 7)
	{
		p = ft_arena_alloc(&a, 17, aligns[i]);
		ft_pin_invariant_msg(p != nullptr, (char *)"aligned alloc");
		ft_pin_invariant_msg(((t_uptr)p & (aligns[i] - 1)) == 0,
			(char *)"align ok");
	}
	ft_destroy_arena(&a);
}

void	test_arena_invalid(void)
{
	t_arena	a;

	a = ft_new_arena_alloc();
	ft_pin_invariant_msg(ft_arena_alloc(&a, 16, 0) == nullptr,
		(char *)"align 0");
	ft_pin_invariant_msg(ft_arena_alloc(&a, 16, 3) == nullptr,
		(char *)"align 3");
	ft_pin_invariant_msg(ft_arena_alloc(&a, 16, 6) == nullptr,
		(char *)"align 6");
	ft_pin_invariant_msg(ft_arena_alloc(&a, 0, 8) == nullptr,
		(char *)"size 0");
	ft_pin_invariant_msg(ft_arena_alloc(&a, (t_size)-1, 8) == nullptr,
		(char *)"oversize");
	ft_destroy_arena(&a);
}

void	test_arena_checkpoint(void)
{
	t_arena				a;
	t_arena_checkpoint	cp;
	void				*p1;
	void				*p2;
	void				*p3;

	a = ft_new_arena_alloc();
	p1 = ft_arena_alloc(&a, 64, 8);
	cp = ft_arena_checkpoint(&a);
	p2 = ft_arena_alloc(&a, 128, 8);
	ft_pin_invariant_msg(p2 != nullptr, (char *)"after cp");
	ft_arena_rewind(&a, cp);
	p3 = ft_arena_alloc(&a, 128, 8);
	ft_pin_invariant_msg(p3 == p2, (char *)"rewind addr");
	(void)p1;
	ft_arena_rewind_clean(&a, cp);
	p3 = ft_arena_alloc(&a, 64, 8);
	ft_pin_invariant_msg(p3 != nullptr, (char *)"after clean");
	ft_destroy_arena(&a);
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	ft_printf("Testing arena allocator...\n");
	test_arena_basic();
	test_arena_alignment();
	test_arena_invalid();
	test_arena_checkpoint();
	ft_printf("  arena: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
