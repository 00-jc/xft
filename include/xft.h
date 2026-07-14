/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/10 00:31:01 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_H
# define XFT_H

# ifdef __cplusplus

extern "C"
{

# endif

# if !defined(__x86_64__) && !defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)
# error "Cannot compile freestanding on this arch without FT_REQUIRE_LIBC"
# endif

# if !defined(__linux__)
# error "For now this library is linux only"
# endif

# include "primitives.h"
# include "bmi.h"
# include "cstr.h"
# include "mem.h"
# include "hash.h"
# include "math.h"
# include "ctype.h"
# include "io.h"
# include "vec.h"
# include "map.h"
# include "macros.h"
# include "tokenizer.h"
# include "hint.h"
# include "timing.h"
# include "perf.h"
# include "tailor.h"
# include "str.h"
# include "syscalls.h"
# include "rt.h"
# include "fmt.h"
# include "atomics.h"

#ifdef __cplusplus
}
#endif

#endif
