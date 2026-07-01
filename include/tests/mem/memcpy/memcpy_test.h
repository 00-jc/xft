/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMCPY_TEST_H
# define MEMCPY_TEST_H

# include "private/test.h"

void	test_memcpy_basic(void);
void	test_memcpy_misaligned(void);
void	test_memcpy_large(void);
void	test_memcpy(t_test *t);

#endif
