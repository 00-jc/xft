/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "private/test.h"

void	test_memchr(t_test *t);
void	test_memcmp(t_test *t);
void	test_memcpy(t_test *t);
void	test_memmove(t_test *t);
void	test_memset(t_test *t);
void	test_bzero(t_test *t);
void	test_streaming_mem(t_test *t);
void	test_strlen(t_test *t);
void	test_cstr(t_test *t);
void	test_vec(t_test *t);
void	test_str(t_test *t);
void	test_map(t_test *t);
void	test_murmur(t_test *t);
void	test_xxh3(t_test *t);
void	test_bmi(t_test *t);
void	test_arena(t_test *t);
void	test_arena_extend(t_test *t);
void	test_gpa_bulk(t_test *t);
void	test_vtables(t_test *t);
void	test_xoshiro(t_test *t);

#endif
