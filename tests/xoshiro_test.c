/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xoshiro_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/14 20:09:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"
#include "rng.h"

void	test_xoshiro_basic(void);
void	test_xoshiro_not_constant(void);
void	test_xoshiro_state_changes(void);
void	test_xoshiro_init_diff(void);

void	test_xoshiro_basic(void)
{
	t_xoshiro							x;
	t_u64a __attribute__	((unused))	r;

	ft_xoshiro_init(x);
	r = ft_xoshiro256ss(x);
	(void)r;
}

void	test_xoshiro_not_constant(void)
{
	t_xoshiro	x;
	t_u64a		a;
	t_u64a		b;

	ft_xoshiro_init(x);
	a = ft_xoshiro256ss(x);
	b = ft_xoshiro256ss(x);
	ft_pin_invariant_msg(a != b, (char *)"xoshiro not constant");
}

void	test_xoshiro_state_changes(void)
{
	t_xoshiro	x;
	t_xoshiro	copy;
	int			i;
	int			same;

	ft_xoshiro_init(x);
	i = 0;
	while (i < 4)
	{
		copy[i] = x[i];
		i++;
	}
	ft_xoshiro256ss(x);
	same = 1;
	i = 0;
	while (i < 4)
	{
		if (x[i] != copy[i])
			same = 0;
		i++;
	}
	ft_pin_invariant_msg(same == 0, (char *)"same != 0");
}

void	test_xoshiro_init_diff(void)
{
	t_xoshiro	a;
	t_xoshiro	b;
	int			i;
	int			diff;

	ft_xoshiro_init(a);
	ft_xoshiro_init(b);
	diff = 0;
	i = 0;
	while (i < 4)
	{
		if (a[i] != b[i])
			diff = 1;
		i++;
	}
	ft_pin_invariant_msg(diff == 1, (char *)"diff != 1");
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	ft_printf("Testing ft_xoshiro256**...\n");
	test_xoshiro_basic();
	test_xoshiro_not_constant();
	test_xoshiro_state_changes();
	test_xoshiro_init_diff();
	ft_printf("  ft_xoshiro256**: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
