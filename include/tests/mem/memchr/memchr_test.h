/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMCHR_TEST_H
# define MEMCHR_TEST_H

# include "private/test.h"

void	test_memchr_basic(void);
void	test_memchr_edge(void);
void	test_memchr_misaligned(void);
void	test_memchr_long(void);
void	test_memchr(t_test *t);

#endif
