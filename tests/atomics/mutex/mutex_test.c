/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/atomics/mutex/mutex_test.h"

static void	mutex_unlock_unlocked(void)
{
	t_mutex	mutex;

	xft_mutex_init(&mutex);
	xft_mutex_unlock(&mutex);
	xft_mutex_unlock(&mutex);
	xft_pin_invariant_msg(atomic_load(&mutex) == xft_unlocked,
		xft_fatptr((t_u8 *)"mutex: unlock unlocked",
			sizeof("mutex: unlock unlocked") - 1));
}

static void	mutex_unlock_contested(void)
{
	t_mutex	mutex;

	atomic_init(&mutex, xft_contested);
	xft_mutex_unlock(&mutex);
	xft_mutex_unlock(&mutex);
	xft_pin_invariant_msg(atomic_load(&mutex) == xft_unlocked,
		xft_fatptr((t_u8 *)"mutex: unlock contested",
			sizeof("mutex: unlock contested") - 1));
}

static void	mutex_unlock_twice(const t_mutex_type type)
{
	t_mutex	mutex;

	xft_mutex_init(&mutex);
	xft_mutex_lock(&mutex, type);
	xft_mutex_unlock(&mutex);
	xft_mutex_unlock(&mutex);
	xft_pin_invariant_msg(atomic_load(&mutex) == xft_unlocked,
		xft_fatptr((t_u8 *)"mutex: unlock twice",
			sizeof("mutex: unlock twice") - 1));
	xft_mutex_lock(&mutex, type);
	xft_pin_invariant_msg(atomic_load(&mutex) == xft_locked,
		xft_fatptr((t_u8 *)"mutex: relock",
			sizeof("mutex: relock") - 1));
	xft_mutex_unlock(&mutex);
}

void	test_mutex(t_test *t)
{
	xft_test_print(t, "Testing mutex...\n");
	mutex_unlock_unlocked();
	mutex_unlock_contested();
	mutex_unlock_twice(xft_lock_fast);
	mutex_unlock_twice(xft_lock_busy);
	mutex_unlock_twice(xft_lock_slow);
	xft_test_print(t, "  mutex: OK\n");
}
