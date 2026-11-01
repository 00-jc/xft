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
# include <xft/soa.h>
# include <xft/types/xft_p_tailor_types.h>

t_plankb			xft_get_kb(t_tailor_job *j)\
						__attribute__((__nonnull__(1)));

const t_soa_context	*xft__tailor_ctx(void)\
						__attribute__((const, __returns_nonnull__));

t_result			xft_tailor_units(t_tailor *t, t_tailor_units *u,\
						t_size size)\
						__attribute__((__nonnull__(1, 2)));

t_result			xft_tailor_unit(t_any unit)\
						__attribute__((__nonnull__(1)));

t_result			xft_tailor_prepare(t_tailor_job *j)\
						__attribute__((__nonnull__(1)));

t_result			xft_tailor_sample(t_tailor_job *j)\
						__attribute__((__nonnull__(1)));

t_result			xft_tailor_finish(t_tailor_job *j)\
						__attribute__((__nonnull__(1)));

t_buffer			xft_tailor_survivors(t_tailor_job *j, const t_soa *soa,\
						t_u64a threshold, t_plankb plan)\
						__attribute__((__nonnull__(1, 2)));

t_result			xft_bootstrap(t_tailor_job *j, t_buffer surv,\
						t_plankb plan)\
						__attribute__((__nonnull__(1)));

#endif
