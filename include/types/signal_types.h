/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:27:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/08 23:05:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_TYPES_H
# define SIGNAL_TYPES_H

# include "primitives.h"

# if defined(FT_REQUIRE_LIBC) || (!defined(__x86_64__) && !defined(__aarch64__))

#  include <signal.h>

typedef sigset_t	t_sigset;

# else

typedef t_u64a		t_sigset;

# endif

#endif
