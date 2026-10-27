/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexmap_bench.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEXMAP_BENCH_H
# define INDEXMAP_BENCH_H

# include <xft/indexmap.h>

typedef enum e_imap_bench : t_u32
{
	IMAP_BENCH_FILL = 4096,
	IMAP_BENCH_KEYS = 8192,
	IMAP_BENCH_LARGE_FILL = 1048576,
}	t_imap_bench;

t_gpa		*xft_get_bench_imap_gpa(void);
t_u64a		*xft_get_bench_imap_keys(void);
t_buffer	xft_imap_bench_key(t_size i);
t_indexmap	*xft_get_bench_imap_filled(void);
t_u64a		*xft_get_bench_imap_large_keys(void);
t_buffer	xft_imap_bench_large_key(t_size i);
t_indexmap	*xft_get_bench_imap_large_filled(void);

void		xft_imap_bench_insert_grow(t_any ptr);
void		xft_imap_bench_insert_reserved(t_any ptr);
void		xft_imap_bench_lookup_hit(t_any ptr);
void		xft_imap_bench_lookup_miss(t_any ptr);
void		xft_imap_bench_delete_insert(t_any ptr);
void		xft_imap_bench_large_lookup_hit(t_any ptr);
void		xft_imap_bench_large_lookup_miss(t_any ptr);
void		xft_imap_bench_large_delete_insert(t_any ptr);

#endif
