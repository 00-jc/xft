/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_vec_push_get(t_allocator a);
void	test_vec_pop(t_allocator a);
void	test_vec_extend(t_allocator a);
void	test_vec_clear_reuse(t_allocator a);

void	test_vec_push_get(t_allocator a)
{
	t_vec		v;
	int			val;
	const int	*got;

	v = ft_vec(a, 4, sizeof(int));
	ft_pin_invariant(v.buf.mem != nullptr);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 0);
	val = 42;
	ft_pin_invariant(ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int)));
	val = 99;
	ft_pin_invariant(ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int)));
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 2);
	got = ft_vec_get(&v, 0, sizeof(int));
	ft_pin_invariant(got && *got == 42);
	got = ft_vec_get(&v, 1, sizeof(int));
	ft_pin_invariant(got && *got == 99);
	ft_pin_invariant(ft_vec_get(&v, 2, sizeof(int)) == nullptr);
	ft_vec_destroy(a, &v);
}

void	test_vec_pop(t_allocator a)
{
	t_vec	v;
	int		val;
	int		out;

	v = ft_vec(a, 4, sizeof(int));
	val = 10;
	ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	val = 20;
	ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	val = 30;
	ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	ft_pin_invariant(ft_vec_popmv(&v, &out, sizeof(int)));
	ft_pin_invariant(out == 30);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 2);
	ft_vec_pop(&v);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 1);
	ft_vec_destroy(a, &v);
}

void	test_vec_extend(t_allocator a)
{
	t_vec		v;
	int			data[5];
	const int	*got;
	int			i;

	v = ft_vec(a, 2, sizeof(int));
	i = 0;
	while (i < 5)
	{
		data[i] = i * 10;
		i++;
	}
	ft_pin_invariant(ft_vec_extend(a, &v,
			(t_buffer){.mem = (t_u8 *)data, .size = sizeof(data)},
			sizeof(int)));
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 5);
	got = ft_vec_get(&v, 3, sizeof(int));
	ft_pin_invariant(got && *got == 30);
	got = ft_vec_get(&v, 4, sizeof(int));
	ft_pin_invariant(got && *got == 40);
	ft_vec_destroy(a, &v);
}

void	test_vec_clear_reuse(t_allocator a)
{
	t_vec		v;
	int			val;
	const int	*got;

	v = ft_vec(a, 8, sizeof(int));
	val = 100;
	ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	val = 200;
	ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 2);
	ft_vec_clear(&v);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 0);
	val = 300;
	ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	got = ft_vec_get(&v, 0, sizeof(int));
	ft_pin_invariant(got && *got == 300);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 1);
	ft_vec_destroy(a, &v);
}

int	main(void)
{
	t_gpa		gpa;
	t_allocator	a;

	gpa = ft_gpa();
	a = ft_gpa_allocator(&gpa);
	ft_printf("Testing t_vec...\n");
	test_vec_push_get(a);
	test_vec_pop(a);
	test_vec_extend(a);
	test_vec_clear_reuse(a);
	ft_gpa_destroy(&gpa);
	ft_printf("  t_vec: OK\n");
	return (0);
}
