/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_rt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:20:44 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_RT_H
# define XFT_P_RT_H

# include <xft/rt.h>

# ifndef XFT_NO_RT

# endif

# if defined(__x86_64__)

typedef enum e_xft_tls_layout : t_u8
{
	xft_tls_tcb_after = 1,
}	t_xft_tls_layout;

# else

typedef enum e_xft_tls_layout : t_u8
{
	xft_tls_tcb_after = 0,
}	t_xft_tls_layout;

# endif

t_u32a	xft_cache_line_size(void)\
			__attribute__((const));

#endif
