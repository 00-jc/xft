/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xoshiro_test.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XOSHIRO_TEST_H
# define XOSHIRO_TEST_H

# include "private/test.h"
# include "rng.h"

void	test_xoshiro_basic(void);
void	test_xoshiro_not_constant(void);
void	test_xoshiro_state_changes(void);
void	test_xoshiro_init_diff(void);
void	test_xoshiro(t_test *t);

#endif
