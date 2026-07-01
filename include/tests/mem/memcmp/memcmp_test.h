/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMCMP_TEST_H
# define MEMCMP_TEST_H

# include "private/test.h"

void	test_memcmp_basic(void);
void	test_memcmp_binary(void);
void	test_memcmp_long(void);
void	test_memcmp_misaligned(void);
void	test_memcmp(t_test *t);

#endif
