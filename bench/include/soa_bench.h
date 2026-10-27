/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_bench.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOA_BENCH_H
# define SOA_BENCH_H

# include <xft/soa.h>

typedef enum e_soa_bench : t_u16
{
	SOA_BENCH_FIELDS = 5,
	SOA_BENCH_FILL = 4096,
}	t_soa_bench;

typedef struct s_soa_bench_particle
{
	t_u64a	id;
	t_i32a	x;
	t_i32a	y;
	t_i32a	vx;
	t_i32a	vy;
}	t_soa_bench_particle;

t_gpa					*xft_get_bench_soa_gpa(void);
const t_soa_context		*xft_get_bench_soa_ctx(void);
t_soa_bench_particle	xft_soa_bench_make(t_size i);
t_soa					xft_soa_bench_filled(t_allocator a);

void					xft_soa_bench_append(t_any ptr);
void					xft_soa_bench_append_reserved(t_any ptr);
void					xft_soa_bench_append_unchecked(t_any ptr);
void					xft_soa_bench_update(t_any ptr);
void					xft_soa_bench_aos_update(t_any ptr);
void					xft_soa_bench_read(t_any ptr);
void					xft_soa_bench_column_sum(t_any ptr);

#endif
