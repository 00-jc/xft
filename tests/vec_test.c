/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_vec_push_get(void);
void	test_vec_pop(void);
void	test_vec_extend(void);
void	test_vec_clear_reuse(void);

void	test_vec_push_get(void)
{
	t_vec		v;
	int			val;
	const int	*got;

	v = ft_vec_new(4, sizeof(int));
	ft_pin_invariant(v.data != nullptr);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 0);
	val = 42;
	ft_pin_invariant(ft_vec_push_back(&v, (t_u8 *)&val, sizeof(int)));
	val = 99;
	ft_pin_invariant(ft_vec_push_back(&v, (t_u8 *)&val, sizeof(int)));
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 2);
	got = ft_vec_get(&v, 0, sizeof(int));
	ft_pin_invariant(got && *got == 42);
	got = ft_vec_get(&v, 1, sizeof(int));
	ft_pin_invariant(got && *got == 99);
	ft_pin_invariant(ft_vec_get(&v, 2, sizeof(int)) == nullptr);
	ft_vec_free(&v);
}

void	test_vec_pop(void)
{
	t_vec	v;
	int		val;
	int		out;

	v = ft_vec_new(4, sizeof(int));
	val = 10;
	ft_vec_push_back(&v, (t_u8 *)&val, sizeof(int));
	val = 20;
	ft_vec_push_back(&v, (t_u8 *)&val, sizeof(int));
	val = 30;
	ft_vec_push_back(&v, (t_u8 *)&val, sizeof(int));
	ft_pin_invariant(ft_vec_popmv(&v, &out, sizeof(int)));
	ft_pin_invariant(out == 30);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 2);
	ft_vec_pop(&v);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 1);
	ft_vec_free(&v);
}

void	test_vec_extend(void)
{
	t_vec		v;
	int			data[5];
	const int	*got;
	int			i;

	v = ft_vec_new(2, sizeof(int));
	i = 0;
	while (i < 5)
	{
		data[i] = i * 10;
		i++;
	}
	ft_pin_invariant(ft_vec_extend(&v, (t_u8 *)data, sizeof(int), 5));
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 5);
	got = ft_vec_get(&v, 3, sizeof(int));
	ft_pin_invariant(got && *got == 30);
	got = ft_vec_get(&v, 4, sizeof(int));
	ft_pin_invariant(got && *got == 40);
	ft_vec_free(&v);
}

void	test_vec_clear_reuse(void)
{
	t_vec		v;
	int			val;
	const int	*got;

	v = ft_vec_new(8, sizeof(int));
	val = 100;
	ft_vec_push_back(&v, (t_u8 *)&val, sizeof(int));
	val = 200;
	ft_vec_push_back(&v, (t_u8 *)&val, sizeof(int));
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 2);
	ft_vec_clear(&v);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 0);
	val = 300;
	ft_vec_push_back(&v, (t_u8 *)&val, sizeof(int));
	got = ft_vec_get(&v, 0, sizeof(int));
	ft_pin_invariant(got && *got == 300);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 1);
	ft_vec_free(&v);
}

int	main(void)
{
	ft_printf("Testing t_vec...\n");
	test_vec_push_get();
	test_vec_pop();
	test_vec_extend();
	test_vec_clear_reuse();
	ft_printf("  t_vec: OK\n");
	return (0);
}
