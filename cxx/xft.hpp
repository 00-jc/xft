/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/10 00:30:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_HPP
# define XFT_HPP

/* mirrors the exact module list include/xft.h aggregates, using the cxx/
 * wrapper of each so the C++ additions (e.g. xft::vec::Vec<T>) come
 * along too. */

# include "primitives.hpp"
# include "bmi.hpp"
# include "cstr.hpp"
# include "mem.hpp"
# include "hash.hpp"
# include "math.hpp"
# include "ctype.hpp"
# include "io.hpp"
# include "vec.hpp"
# include "map.hpp"
# include "macros.hpp"
# include "tokenizer.hpp"
# include "hint.hpp"
# include "timing.hpp"
# include "perf.hpp"
# include "tailor.hpp"
# include "str.hpp"
# include "syscalls.hpp"
# include "rt.hpp"
# include "fmt.hpp"
# include "atomics.hpp"

#endif
