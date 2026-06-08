/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_allocator.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 04:14:01 by username          #+#    #+#             */
/*   Updated: 2026/06/06 04:38:06 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_ALLOCATOR_H
# define GENERAL_ALLOCATOR_H

# include "types/general_allocator_types.h"

t_gpa		ft_gpa(void);
void		ft_gpa_destroy(t_gpa *gpa);
t_buffer	ft_gpa_alloc(void *alloc, size_t size, size_t align);
t_buffer	ft_gpa_realloc(void *alloc, t_buffer buf, size_t newsize,
				size_t align);
void		ft_gpa_free(void *allocator, t_buffer buf);
t_buffer	ft_alloc_clone(void *self, t_buffer buffer)\
				__attribute__((__nonnull__(1)));

#endif
