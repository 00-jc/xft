/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/vtables/vtables_test.h"

void	test_vtables(t_test *t)
{
	ft_test_print(t, "Testing allocator vtables...\n");
	test_palloc_vtable();
	test_arena_vtable();
	test_gpa_vtable();
	test_gpa_freelist();
	ft_test_print(t, "  vtables: OK\n");
}
