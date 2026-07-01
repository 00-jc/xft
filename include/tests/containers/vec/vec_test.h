/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_TEST_H
# define VEC_TEST_H

# include "private/test.h"

void	test_vec_push_get(t_allocator a);
void	test_vec_pop(t_allocator a);
void	test_vec_extend(t_allocator a);
void	test_vec_clear_reuse(t_allocator a);
void	test_vec(t_test *t);

#endif
