/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_perf_types.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_PERF_TYPES_H
# define XFT_P_PERF_TYPES_H

# include <xft/primitives.h>

typedef struct s_perf_read
{
	t_u64	nr;
	t_u64	enabled;
	t_u64	running;
	t_u64	val[9];
}	t_perf_read;

#endif
