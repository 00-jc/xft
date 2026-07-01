/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:10 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 23:42:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "tests/tests.h"

__attribute__((__nonnull__(1), used, __always_inline__))
inline void	run_all_tests(t_test *t)
{
	test_memchr(t);
	test_memcmp(t);
	test_memcpy(t);
	test_memmove(t);
	test_memset(t);
	test_bzero(t);
	test_streaming_mem(t);
	test_strlen(t);
	test_cstr(t);
	test_vec(t);
	test_str(t);
	test_map(t);
	test_murmur(t);
	test_xxh3(t);
	test_bmi(t);
	test_arena(t);
	test_arena_extend(t);
	test_gpa_bulk(t);
	test_vtables(t);
	test_xoshiro(t);
}

__attribute__((__always_inline__))
inline int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	t_test	t;

	ft_test_init(&t);
	run_all_tests(&t);
	(void)argc;
	(void)argv;
	(void)envp;
	ft_writer_flush(&t.writer);
	return (0);
}
