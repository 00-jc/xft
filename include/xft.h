/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 18:11:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_H
# define XFT_H

# ifdef __cplusplus

extern "C"
{

# endif

# if !defined(__x86_64__) && !defined(FT_REQUIRES_LIBC)
# error "Cannot compile on non x86_64 without FT_REQUIRES_LIBC"
# endif

# if !defined(__linux__)
# error "For now this library is linux only"
# endif

# include "primitives.h"
# include "cstr.h"
# include "mem.h"
# include "hash.h"
# include "math.h"
# include "ctype.h"
# include "io.h"
# include "conv.h"
# include "vec.h"
# include "map.h"
# include "macros.h"
# include "tokenizer.h"
# include "hint.h"
# include "timing.h"
# include "perf.h"
# include "tailor.h"
# include "str.h"
# include "syscall.h"
# include "rt.h"
# include "fmt.h"

#ifdef __cplusplus
}
#endif

#endif
