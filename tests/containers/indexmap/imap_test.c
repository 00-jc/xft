/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imap_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/indexmap/imap_test.h"

void	test_indexmap(t_test *t)
{
	t_gpa		gpa;
	t_allocator	a;

	gpa = xft_new_gpa();
	a = xft_gpa_allocator(&gpa);
	xft_test_print(t, "Testing t_indexmap...\n");
	test_imap_insert_lookup(a);
	test_imap_delete(a);
	test_imap_overwrite(a);
	test_imap_many(a);
	test_imap_churn(a);
	test_imap_dense(a);
	test_imap_seeded(a);
	xft_gpa_destroy(&gpa);
	xft_test_print(t, "  t_indexmap: OK\n");
}
