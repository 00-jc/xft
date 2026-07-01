/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_extend_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/arena/arena_extend_test.h"

void	test_arena_extend(t_test *t)
{
	ft_test_print(t, "Testing arena extend...\n");
	test_extend_trigger();
	test_extend_rewind_reuse();
	test_extend_rewind_grow();
	test_extend_clean_releases();
	ft_test_print(t, "  arena extend: OK\n");
}
