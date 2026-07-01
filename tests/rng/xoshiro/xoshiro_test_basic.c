/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xoshiro_test_basic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/rng/xoshiro/xoshiro_test.h"

void	test_xoshiro_basic(void)
{
	t_xoshiro							x;
	t_u64a __attribute__	((unused))	r;

	ft_xoshiro_init(x);
	r = ft_xoshiro256ss(x);
	(void)r;
}
