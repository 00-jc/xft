/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_test.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:45 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_TEST_H
# define ARENA_TEST_H

# include "test.h"
# include "alloc.h"

void	test_arena_basic(void);
void	test_arena_uniq(t_arena *a, t_any buf);
void	test_arena_alignment(void);
void	test_arena_invalid(void);
void	test_arena_checkpoint(void);
void	test_arena(t_test *t);

#endif
