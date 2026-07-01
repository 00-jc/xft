/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murmur_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MURMUR_TEST_H
# define MURMUR_TEST_H

# include "private/test.h"

void	test_murmur_deterministic(void);
void	test_murmur_diff_input(void);
void	test_murmur_seed(void);
void	test_murmur_lengths(void);
void	test_murmur(t_test *t);

#endif
