/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_hugepage.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 19:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_HUGEPAGE_H
# define FT_P_HUGEPAGE_H

# include "alloc/page_alloc.h"
# include "bmi.h"

size_t	ft_match_hugepage(size_t size)\
			__attribute__((const));
int		ft_match_hugepage_flags(size_t page_size)\
			__attribute__((const));

#endif
