/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERF_H
# define PERF_H

# ifdef __linux__

#  include <xft/types/perf_types.h>

t_result		xft_bind_process_to_cpu(t_u32 cpu);
t_result		xft_perf_create_counters(t_perf_counters c)\
					__attribute__((__nonnull__(1)));
void			xft_perf_counters_reset(t_perf_counters c)\
					__attribute__((__nonnull__(1)));
void			xft_perf_counters_start(t_perf_counters c)\
					__attribute__((__nonnull__(1)));
void			xft_perf_counters_stop(t_perf_counters c)\
					__attribute__((__nonnull__(1)));
void			xft_perf_start_sample(t_perf_counters c, t_perf_sample *s)\
					__attribute__((__nonnull__(1, 2)));
t_result		xft_perf_collect_sample(t_size n,\
					t_perf_counters c, t_perf_sample *s)\
					__attribute__((__nonnull__(2, 3)));
void			xft_perf_destroy_counters(t_perf_counters c)\
					__attribute__((__nonnull__(1)));

# else

#  error "perf.h is linux only: it is built on perf_event_open"

# endif
#endif
