/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bulk_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"
#include "alloc.h"

#define BULK_N		512
#define BULK_SIZES	4

static void	test_bulk_same_size(void);
static void	test_bulk_mixed_sizes(void);
static void	test_bulk_reuse(void);

void	test_bulk_same_size(void)
{
	t_buffer	bufs[BULK_N];
	t_gpa		gpa;
	int			i;

	gpa = ft_gpa();
	ft_pin_invariant_msg(gpa.slab != nullptr, (char *)"gpa init");
	i = -1;
	while (++i < BULK_N)
	{
		bufs[i] = ft_gpa_alloc(&gpa, 64, 8);
		ft_pin_invariant_msg(bufs[i].mem != nullptr, (char *)"bulk alloc");
		ft_pin_invariant_msg(bufs[i].size >= 64, (char *)"bulk size");
		ft_pin_invariant_msg(((t_uptr)bufs[i].mem & 7) == 0,
			(char *)"bulk align");
		*(t_u64 *)bufs[i].mem = (t_u64)i;
	}
	i = -1;
	while (++i < BULK_N)
		ft_pin_invariant_msg(*(t_u64 *)bufs[i].mem == (t_u64)i,
			(char *)"bulk rw");
	i = BULK_N;
	while (--i >= 0)
		ft_gpa_free(&gpa, bufs[i]);
	ft_gpa_destroy(&gpa);
}

void	test_bulk_mixed_sizes(void)
{
	static const t_size	sizes[BULK_SIZES] = {16, 64, 256, 1024};
	t_buffer			bufs[BULK_N];
	t_gpa				gpa;
	int					i;

	gpa = ft_gpa();
	ft_pin_invariant_msg(gpa.slab != nullptr, (char *)"gpa init mixed");
	i = -1;
	while (++i < BULK_N)
	{
		bufs[i] = ft_gpa_alloc(&gpa, sizes[i % BULK_SIZES], 8);
		ft_pin_invariant_msg(bufs[i].mem != nullptr, (char *)"mixed alloc");
		ft_pin_invariant_msg(bufs[i].size >= sizes[i % BULK_SIZES],
			(char *)"mixed size");
		*(t_u8 *)bufs[i].mem = (t_u8)(i & 0xff);
	}
	i = -1;
	while (++i < BULK_N)
		ft_pin_invariant_msg(*(t_u8 *)bufs[i].mem == (t_u8)(i & 0xff),
			(char *)"mixed rw");
	i = -1;
	while (++i < BULK_N)
		ft_gpa_free(&gpa, bufs[i]);
	ft_gpa_destroy(&gpa);
}

void	test_bulk_reuse(void)
{
	t_buffer	bufs[BULK_N];
	t_gpa		gpa;
	t_buffer	b;
	int			i;

	gpa = ft_gpa();
	ft_pin_invariant_msg(gpa.slab != nullptr, (char *)"gpa init reuse");
	i = -1;
	while (++i < BULK_N)
		bufs[i] = ft_gpa_alloc(&gpa, 128, 8);
	i = BULK_N;
	while (--i >= 0)
		ft_gpa_free(&gpa, bufs[i]);
	i = -1;
	while (++i < BULK_N)
	{
		b = ft_gpa_alloc(&gpa, 128, 8);
		ft_pin_invariant_msg(b.mem != nullptr, (char *)"reuse alloc");
		ft_pin_invariant_msg(b.size >= 128, (char *)"reuse size");
		ft_gpa_free(&gpa, b);
	}
	ft_gpa_destroy(&gpa);
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	ft_printf("Testing gpa bulk alloc/free...\n");
	test_bulk_same_size();
	test_bulk_mixed_sizes();
	test_bulk_reuse();
	ft_printf("  gpa bulk: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
