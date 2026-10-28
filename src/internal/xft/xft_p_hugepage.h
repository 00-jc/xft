/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_hugepage.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_HUGEPAGE_H
# define XFT_P_HUGEPAGE_H

# include <xft/alloc/page_alloc.h>

t_size	xft_match_hugepage(t_size size)\
			__attribute__((const));
int		xft_match_hugepage_flags(t_u64 page_size)\
			__attribute__((const));

#endif
