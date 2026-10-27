/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 15:52:08 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_TYPES_H
# define MEM_TYPES_H

# include <xft/primitives.h>
# include <xft/bmi.h>

typedef enum e_xft_bytemask : t_u64
{
	LONES_64 = 0x0101010101010101,
	HIGHS_64 = 0x8080808080808080,
}	t_xft_bytemask;

# ifndef XFT_PAGE_ALIGN
#  define XFT_PAGE_ALIGN 0x1000ULL
# endif

#endif
