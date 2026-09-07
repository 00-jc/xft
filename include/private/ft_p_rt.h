/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:21:24 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/08 23:55:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_RT_H
# define FT_P_RT_H

# include "rt.h"

# ifndef FT_NO_RT

t_size			ft_get_envp_size(t_rt_arr envp)\
					__attribute__((__nonnull__(1), pure));
void			ft__get_thread_info(t_xft_rt *rt)\
					__attribute__((__nonnull__(1)));
void			ft_get_auxv_size(t_xft_rt *rt, t_auxv auxv)\
					__attribute__((__nonnull__(1, 2)));

# endif

#endif
