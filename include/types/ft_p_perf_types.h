/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_perf_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:02:57 by username          #+#    #+#             */
/*   Updated: 2026/06/28 16:02:59 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_PERF_TYPES_H
# define FT_P_PERF_TYPES_H

# include "primitives.h"

typedef struct s_perf_read
{
	t_u64	nr;
	t_u64	enabled;
	t_u64	running;
	t_u64	val[9];
}	t_perf_read;

#endif
