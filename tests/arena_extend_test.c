/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_extend_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"
#include "alloc.h"

static void	test_extend_trigger(void);
static void	test_extend_rewind_reuse(void);
static void	test_extend_rewind_grow(void);
static void	test_extend_clean_releases(void);

void	test_extend_trigger(void)
{
	t_arena		a;
	t_hugepage	*first;
	void		*p;
	size_t		big;

	a = ft_new_arena_alloc();
	first = a.current;
	ft_pin_invariant_msg(first->next == nullptr, (char *)"no next yet");
	big = first->total - first->used - 128;
	p = ft_arena_alloc(&a, big, 16);
	ft_pin_invariant_msg(p != nullptr, (char *)"fill page");
	ft_pin_invariant_msg(a.current == first, (char *)"still first");
	p = ft_arena_alloc(&a, 4096, 16);
	ft_pin_invariant_msg(p != nullptr, (char *)"overflow alloc");
	ft_pin_invariant_msg(a.current != first, (char *)"moved fwd");
	ft_pin_invariant_msg(a.current->prev == first, (char *)"prev link");
	ft_pin_invariant_msg(first->next == a.current, (char *)"next link");
	ft_destroy_arena(&a);
}

void	test_extend_rewind_reuse(void)
{
	t_arena				a;
	t_arena_checkpoint	cp;
	t_hugepage			*second;
	void				*ptrs[2];
	size_t				big;

	a = ft_new_arena_alloc();
	big = a.current->total - a.current->used - 128;
	ft_arena_alloc(&a, big, 16);
	cp = ft_arena_checkpoint(&a);
	ptrs[0] = ft_arena_alloc(&a, 4096, 16);
	second = a.current;
	ft_pin_invariant_msg(second != cp.location, (char *)"new page");
	ft_arena_rewind(&a, cp);
	ft_pin_invariant_msg(a.current == cp.location, (char *)"rewound");
	ptrs[1] = ft_arena_alloc(&a, 4096, 16);
	ft_pin_invariant_msg(a.current == second, (char *)"reused page");
	ft_pin_invariant_msg(ptrs[1] == ptrs[0], (char *)"same addr");
	ft_destroy_arena(&a);
}

void	test_extend_rewind_grow(void)
{
	t_arena				a;
	t_arena_checkpoint	cp;
	t_hugepage			*pages[2];
	void				*p;
	size_t				big;

	a = ft_new_arena_alloc();
	pages[0] = a.current;
	big = pages[0]->total - pages[0]->used - 128;
	ft_arena_alloc(&a, big, 16);
	cp = ft_arena_checkpoint(&a);
	p = ft_arena_alloc(&a, 4096, 16);
	ft_pin_invariant_msg(p != nullptr, (char *)"first grow");
	pages[1] = a.current;
	ft_arena_rewind(&a, cp);
	ft_pin_invariant_msg(a.current == pages[0], (char *)"rewound");
	p = ft_arena_alloc(&a, 4096, 16);
	ft_pin_invariant_msg(p != nullptr, (char *)"realloc");
	ft_pin_invariant_msg(a.current == pages[1], (char *)"reuse");
	ft_destroy_arena(&a);
}

void	test_extend_clean_releases(void)
{
	t_arena				a;
	t_arena_checkpoint	cp;
	t_hugepage			*base;
	size_t				big;
	int					i;

	a = ft_new_arena_alloc();
	base = a.current;
	cp = ft_arena_checkpoint(&a);
	big = base->total - base->used - 128;
	ft_arena_alloc(&a, big, 16);
	i = -1;
	while (++i < 4)
		ft_arena_alloc(&a, 4096, 16);
	ft_arena_rewind_clean(&a, cp);
	ft_pin_invariant_msg(a.current == base, (char *)"back to base");
	ft_pin_invariant_msg(base->next == nullptr, (char *)"chain cleared");
	ft_pin_invariant_msg(ft_arena_alloc(&a, 64, 8) != nullptr,
		(char *)"alloc after clean");
	ft_destroy_arena(&a);
}

int	main(void)
{
	ft_printf("Testing arena extend...\n");
	test_extend_trigger();
	test_extend_rewind_reuse();
	test_extend_rewind_grow();
	test_extend_clean_releases();
	ft_printf("  arena extend: OK\n");
	return (0);
}
