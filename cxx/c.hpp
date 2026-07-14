/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/11 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_HPP
# define C_HPP

/* primitives.h is included raw/unqualified first (through primitives.hpp,
 * which is idempotent via its own header guard): t_u8, t_size, t_buffer,
 * t_result, ... are pure value types with no clashing names, so they stay
 * bare everywhere in this codebase exactly as cxx/primitives.hpp documents.
 * Every other header below is module-owned (structs and functions
 * private to one module, e.g. t_vec/ft_vec_push_back) and gets bundled into
 * this single xft::c namespace instead of the global namespace. It has to be
 * one shared namespace rather than one per module: the C headers freely
 * include each other (vec.h pulls in alloc.h, io.h pulls in mem.h and
 * alloc.h, map.h pulls in vec.h, ...) and each one's own #ifndef guard means
 * it only textually expands once per translation unit - if that single
 * expansion happened inside, say, namespace xft::alloc::c, then a name like
 * t_allocator would only exist there, and every other module's namespace
 * that also needs t_allocator unqualified would fail to compile. Each
 * module's own header (vec.hpp, alloc.hpp, ...) declares
 * `namespace c = xft::c;` as a namespace alias once inside its own
 * `namespace xft::<module>`, so xft::vec::c::t_vec and xft::alloc::c::
 * t_allocator both resolve to this same namespace's members. */

# include "primitives.hpp"

# define restrict	__restrict__
# define _Atomic

namespace xft
{
namespace c
{
extern "C"
{
# include "../include/alloc.h"
# include "../include/atomics.h"
# include "../include/bmi.h"
# include "../include/cstr.h"
# include "../include/ctype.h"
# include "../include/elf.h"
# include "../include/fmt.h"
# include "../include/fuzzer.h"
# include "../include/hash.h"
# include "../include/hint.h"
# include "../include/io.h"
# include "../include/linux.h"
# include "../include/macros.h"
# include "../include/map.h"
# include "../include/math.h"
# include "../include/mem.h"
# include "../include/perf.h"
# include "../include/rng.h"
# include "../include/rt.h"
# include "../include/signals.h"
# include "../include/sort.h"
# include "../include/str.h"
# include "../include/syscalls.h"
# include "../include/tailor.h"
# include "../include/threads.h"
# include "../include/timing.h"
# include "../include/tokenizer.h"
# include "../include/vec.h"
}
}
}

# undef _Atomic
# undef restrict

#endif
