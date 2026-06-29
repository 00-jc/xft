/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report_allocator.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 04:13:10 by username          #+#    #+#             */
/*   Updated: 2026/06/06 04:38:16 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPORT_ALLOCATOR_H
# define REPORT_ALLOCATOR_H

# include "types/report_allocator_primitives.h"

t_reporta	ft_reporta(void);
void		ft_reporta_destroy(t_reporta *gpa)\
				__attribute__((__nonnull__(1)));
t_buffer	ft_reporta_alloc(void *alloc, t_size size, t_size align)\
				__attribute__((__nonnull__(1)));
t_buffer	ft_reporta_realloc(void *alloc, t_buffer buf, t_size newsize,
				t_size align)\
				__attribute__((__nonnull__(1)));
void		ft_reporta_free(void *allocator, t_buffer buf)\
				__attribute__((__nonnull__(1)));

#endif
