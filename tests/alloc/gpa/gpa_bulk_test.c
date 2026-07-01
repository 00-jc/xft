/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bulk_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/gpa/gpa_bulk_test.h"

void	test_gpa_bulk(t_test *t)
{
	ft_test_print(t, "Testing gpa bulk alloc/free...\n");
	test_bulk_same_size();
	test_bulk_mixed_sizes();
	test_bulk_reuse();
	ft_test_print(t, "  gpa bulk: OK\n");
}
