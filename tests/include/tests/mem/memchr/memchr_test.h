/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:45 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMCHR_TEST_H
# define MEMCHR_TEST_H

# include "test.h"

void	test_memchr_basic(void);
void	test_memchr_edge(void);
void	test_memchr_misaligned(void);
void	test_memchr_long(void);
void	test_memchr(t_test *t);

#endif
