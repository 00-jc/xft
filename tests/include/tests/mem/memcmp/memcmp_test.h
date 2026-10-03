/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMCMP_TEST_H
# define MEMCMP_TEST_H

# include "test.h"

void	test_memcmp_basic(void);
void	test_memcmp_binary(void);
void	test_memcmp_long(void);
void	test_memcmp_misaligned(void);
void	test_memcmp(t_test *t);

#endif
