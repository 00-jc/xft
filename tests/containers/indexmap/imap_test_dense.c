/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imap_test_dense.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/indexmap/imap_test.h"

#define IMAP_TEST_DENSE	1000

/* the user owned dense array: keys[0..*n) with the map pointing into it */
static t_buffer	dense_key(t_u64a *keys, t_size i)
{
	return (xft_fatptr((t_u8 *)&keys[i], sizeof(t_u64a)));
}

static void	dense_swap_remove(t_allocator a, t_indexmap *m, t_u64a *keys,
	t_size *n)
{
	t_u64a	gone;
	t_size	idx;

	gone = keys[*n / 2];
	idx = xft_indexmap_delete(m, xft_fatptr((t_u8 *)&gone, sizeof(gone)));
	xft_pin_invariant(idx == *n / 2);
	--*n;
	if (idx == *n)
		return ;
	keys[idx] = keys[*n];
	xft_pin_invariant(xft_indexmap_insert(a, m, dense_key(keys, idx), idx));
	xft_pin_invariant(xft_indexmap_lookup(m,
			xft_fatptr((t_u8 *)&gone, sizeof(gone))) == INDEXMAP_NPOS);
}

void	test_imap_dense(t_allocator a)
{
	t_indexmap	m;
	t_xoshiro	rng;
	t_u64a		keys[IMAP_TEST_DENSE];
	t_size		n;
	t_size		i;

	xft_xoshiro_init(rng);
	m = xft_new_indexmap(a);
	n = 0;
	while (n < IMAP_TEST_DENSE)
	{
		keys[n] = xft_xoshiro256ss(rng);
		xft_pin_invariant(xft_indexmap_insert(a, &m, dense_key(keys, n), n));
		++n;
	}
	while (n > IMAP_TEST_DENSE / 4)
		dense_swap_remove(a, &m, keys, &n);
	xft_pin_invariant(m.count == n);
	i = n;
	while (i-- > 0)
		xft_pin_invariant(xft_indexmap_lookup(&m, dense_key(keys, i)) == i);
	xft_indexmap_destroy(a, &m);
}
