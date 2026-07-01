/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_allocator.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 11:18:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_ALLOCATOR_H
# define GENERAL_ALLOCATOR_H

# include "types/general_allocator_types.h"

t_gpa		ft_gpa(void);
void		ft_gpa_destroy(t_gpa *gpa);
t_buffer	ft_gpa_alloc(void *alloc, t_size size, t_size align);
t_buffer	ft_gpa_realloc(void *alloc, t_buffer buf, t_size newsize,
				t_size align);
void		ft_gpa_free(void *allocator, t_buffer buf);
t_buffer	ft_alloc_clone(void *self, t_buffer buffer)\
				__attribute__((__nonnull__(1)));

#endif
