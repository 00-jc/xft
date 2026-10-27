/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 20:14:38 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 15:56:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOA_H
# define SOA_H

# include <xft/primitives.h>
# include <xft/types/soa_types.h>

t_soa					xft_new_soa(t_allocator allocator,\
							t_size initial_element_capacity,\
							const t_soa_context *__restrict__ const ctx)\
							__attribute__((__nonnull__(3)));

t_result				xft_soa_reserve(t_allocator allocator,\
							t_soa *__restrict__ const soa,\
							const t_soa_context *__restrict__ const ctx,\
							t_size elements_to_reserve)\
							__attribute__((__nonnull__(2, 3)));

t_result				xft_soa_append_from_struct(t_allocator allocator,\
							t_soa *__restrict__ const soa,\
							t_any __restrict__ const _struct,\
							const t_soa_context *__restrict__ const ctx)\
							__attribute__((__nonnull__(2, 3, 4)));

void					xft_soa_append_from_struct_unchecked(\
							t_soa *__restrict__ const soa,\
							t_any __restrict__ const _struct,\
							const t_soa_context *__restrict__ const ctx)\
							__attribute__((__nonnull__(1, 2, 3)));

t_any					xft_soa_fields(const t_soa *__restrict__ const soa,\
							const t_soa_context *__restrict__ const ctx,\
							t_size field_idx)\
							__attribute__((pure, __nonnull__(1, 2),\
								__returns_nonnull__));

void					xft_destroy_soa(t_allocator allocator, t_soa *soa)\
							__attribute__((__nonnull__(2)));

#endif
