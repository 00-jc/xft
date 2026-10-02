/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_allocator.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/08 17:50:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_ALLOCATOR_H
# define GENERAL_ALLOCATOR_H

# include "types/general_allocator_types.h"

t_gpa		xft_gpa(void);
void		xft_gpa_destroy(t_gpa *gpa);
t_buffer	xft_gpa_alloc(t_any alloc, t_size size, t_size align);
t_buffer	xft_gpa_realloc(t_any alloc, t_buffer buf, t_size newsize,
				t_size align);
void		xft_gpa_free(t_any allocator, t_buffer buf);
t_buffer	xft_alloc_clone(t_any self, t_buffer buffer)\
				__attribute__((__nonnull__(1)));

#endif
