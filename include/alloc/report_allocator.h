/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report_allocator.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPORT_ALLOCATOR_H
# define REPORT_ALLOCATOR_H

# include "types/report_allocator_primitives.h"

t_reporta	xft_new_reporta(void);
void		xft_reporta_destroy(t_reporta *gpa)\
				__attribute__((__nonnull__(1)));
t_buffer	xft_reporta_alloc(t_any alloc, t_size size, t_size align)\
				__attribute__((__nonnull__(1)));
t_buffer	xft_reporta_realloc(t_any alloc, t_buffer buf, t_size newsize,
				t_size align)\
				__attribute__((__nonnull__(1)));
void		xft_reporta_free(t_any allocator, t_buffer buf)\
				__attribute__((__nonnull__(1)));

#endif
