/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_TYPES_H
# define SIGNAL_TYPES_H

# include "primitives.h"

# define XFT_SIGSET_SIZE	8

# if (defined(XFT_REQUIRE_LIBC) && !defined(_WIN64)) \
	|| (!defined(__x86_64__) && !defined(__aarch64__))

#  include <signal.h>

typedef sigset_t	t_sigset;

# else

typedef t_u64a		t_sigset;

# endif

#endif
