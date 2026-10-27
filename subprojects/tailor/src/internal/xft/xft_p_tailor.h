/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_tailor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_TAILOR_H
# define XFT_P_TAILOR_H

# include <xft/tailor.h>
# include <xft/sort.h>
# include <xft/types/xft_p_tailor_types.h>

t_plankb		xft_get_kb(t_tailor *t, t_tailor_fn fn)\
					__attribute__((__nonnull__(1, 2)));

t_result		xft_bootstrap(t_tailor *t, t_buffer surv, t_plankb plan,\
					t_blk8r name) __attribute__((__nonnull__(1)));

void			xft_print_summary(t_buffer surv, t_plankb plan,\
					t_tailor_report_ctx ctx,\
					t_u64a data[4])\
					__attribute__((__nonnull__(4)));

t_result		xft_tailor_benchfn(t_tailor *t, t_tailor_fn fn, t_blk8r name)\
					__attribute__((__nonnull__(1)));

#endif
