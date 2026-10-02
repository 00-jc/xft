/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_hugepage.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_HUGEPAGE_H
# define XFT_P_HUGEPAGE_H

# include "alloc/page_alloc.h"
# include "bmi.h"

t_size	xft_match_hugepage(t_size size)\
			__attribute__((const));
int		xft_match_hugepage_flags(t_size page_size)\
			__attribute__((const));

#endif
