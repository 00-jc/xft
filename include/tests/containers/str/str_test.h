/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_TEST_H
# define STR_TEST_H

# include "private/test.h"

void	test_str_new(t_allocator a);
void	test_str_push_back(t_allocator a);
void	test_str_extend(t_allocator a);
void	test_str_remove(t_allocator a);
void	test_str(t_test *t);

#endif
