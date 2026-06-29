/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 21:52:28 by username          #+#    #+#             */
/*   Updated: 2026/06/28 23:42:04 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMING_TYPES_H
# define TIMING_TYPES_H

# include "primitives.h"

# if defined(FT_REQUIRE_LIBC)

#  include <time.h>

typedef struct timespec		t_timespec;

# else

typedef struct s_timespec
{
	t_i64a		tv_sec;
	t_i64a		tv_nsec;
}	t_timespec;

# endif

typedef struct s_tsc
{
	t_i64a		base;
	t_i64a		mult;
}	t_tsc;

#endif
