/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_alloc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAGE_ALLOC_H
# define PAGE_ALLOC_H

# include <stddef.h>
# include <xft/types/page_alloc_types.h>

t_buffer	xft_palloc(t_size size);
t_buffer	xft_palloc_reserve(t_size size);
t_result	xft_palloc_commit(t_any ptr, t_size size)\
				__attribute__((__nonnull__(1)));
t_buffer	xft_palloc_resize(t_buffer b, t_size new_size);
void		xft_palloc_free(t_buffer b);

#endif
