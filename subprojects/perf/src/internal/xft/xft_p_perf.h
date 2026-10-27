/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_perf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_PERF_H
# define XFT_P_PERF_H

# include <xft/perf.h>
# include <xft/types/xft_p_perf_types.h>

const t_hw_counters		*get_hw_counters(void)\
							__attribute__((const));

const t_sw_counters		*get_sw_counters(void)\
							__attribute__((const));

#endif
