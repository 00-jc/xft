/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 16:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOA_TEST_H
# define SOA_TEST_H

# include <xft/test.h>

typedef enum e_soa_test : t_u8
{
	SOA_TEST_FIELDS = 4,
	SOA_TEST_ALIGN = 8,
}	t_soa_test;

typedef struct s_soa_test_elem
{
	t_u8	tag;
	t_u64	id;
	t_u32	val;
	t_u16	small;
}	t_soa_test_elem;

t_buffer		soa_test_ctx_new(t_allocator a);
t_soa_test_elem	soa_test_make(t_size i);
void			soa_test_check(const t_soa *soa, const t_soa_context *ctx,
					t_size i);
void			soa_test_check_aligned(const t_soa *soa,
					const t_soa_context *ctx);
void			test_soa_new(t_allocator a, const t_soa_context *ctx);
void			test_soa_append(t_allocator a, const t_soa_context *ctx);
void			test_soa_grow(t_allocator a, const t_soa_context *ctx);
void			test_soa_reserve(t_allocator a, const t_soa_context *ctx);
void			test_soa(t_test *t);

#endif
