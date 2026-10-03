/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_extend_test.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_EXTEND_TEST_H
# define ARENA_EXTEND_TEST_H

# include "test.h"
# include "alloc.h"

void	test_extend_trigger(void);
void	test_extend_rewind_reuse(void);
void	test_extend_rewind_grow(void);
void	test_extend_clean_releases(void);
void	test_arena_extend(t_test *t);

#endif
