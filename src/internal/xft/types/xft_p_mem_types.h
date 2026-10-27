/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_mem_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/23 13:02:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_MEM_TYPES_H
# define XFT_P_MEM_TYPES_H

# include <xft/primitives.h>

# if !defined(XFT_LLC_SIZE) || XFT_LLC_SIZE == 0
#  define XFT_LLC_SIZE 16777216ULL
# endif

typedef struct s_t_f64_size
{
	t_size		i;
	t_size		blks;
}	t_t_f64_size;

#endif
