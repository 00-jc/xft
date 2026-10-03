/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murmur_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MURMUR_TEST_H
# define MURMUR_TEST_H

# include "test.h"

void	test_murmur_deterministic(void);
void	test_murmur_diff_input(void);
void	test_murmur_seed(void);
void	test_murmur_lengths(void);
void	test_murmur(t_test *t);

#endif
