/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMING_TYPES_H
# define TIMING_TYPES_H

# include "primitives.h"

# if defined(XFT_REQUIRE_LIBC) && !defined(_WIN64)

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
