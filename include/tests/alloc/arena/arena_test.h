/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_test.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_TEST_H
# define ARENA_TEST_H

# include "private/test.h"
# include "alloc.h"

void	test_arena_basic(void);
void	test_arena_uniq(t_arena *a, void *buf);
void	test_arena_alignment(void);
void	test_arena_invalid(void);
void	test_arena_checkpoint(void);
void	test_arena(t_test *t);

#endif
