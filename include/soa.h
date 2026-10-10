/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 20:14:38 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/10 20:44:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOA_H
# define SOA_H

# include "primitives.h"
# include "alloc.h"

typedef struct s_soa_field_meta
{
	t_u32a			alignment;
	t_u32a			size;
	t_u32a			offset_from_struct_base;
}	t_soa_field_meta;

typedef struct	s_soa_context
{
	t_size				total_struct_size;
	t_size				fields_count;
	t_soa_field_meta	entries[];
}	t_soa_context;

typedef struct s_soa
{
	t_any				__restrict__ ptr;
	t_size				occupied_elements;
	t_size				capacity_elements;
	t_size				allocator_bytes_given;
}	t_soa;

t_soa					xft_new_soa(t_allocator allocator,\
							t_size initial_element_capacity,\
							const t_soa_context *__restrict__ const ctx)\
							__attribute__((__nonnull__(3)));

t_result				xft_soa_append_from_struct(t_allocator allocator,\
							t_soa *__restrict__ const soa,\
							t_any __restrict__ const _struct,\
							const t_soa_context *__restrict__ const ctx)\
							__attribute__((__nonnull__(2, 3, 4)));

void					xft_destroy_soa(t_allocator allocator, t_soa *soa)\
							__attribute__((__nonnull__(2)));

#endif
