/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VTABLES_TEST_H
# define VTABLES_TEST_H

# include "private/test.h"
# include "alloc.h"

void	test_palloc_vtable(void);
void	test_palloc_vtable_realloc(t_allocator *alloc, t_buffer buf);
void	test_arena_vtable(void);
void	test_arena_vtable_realloc(t_allocator *alloc, t_buffer buf);
void	test_gpa_vtable(void);
void	test_gpa_vtable_realloc(t_allocator *alloc, t_buffer buf);
void	test_gpa_freelist(void);
void	test_gpa_freelist_advance(t_allocator *alloc);
void	test_vtables(t_test *t);

#endif
