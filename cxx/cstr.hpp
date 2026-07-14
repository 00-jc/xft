/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSTR_HPP
# define CSTR_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace cstr
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: every function keeps its C name, parameter
 * order and return value, just namespaced and marked FT_NOEXCEPT (none of
 * these can throw, they report failure through explicit return values;
 * FT_NOEXCEPT is the C++98 spelling of "never unwinds"). cstr.h has no
 * struct of its own to wrap (cstr_to_str produces a t_str, already
 * wrapped by xft::str::Str); the allocator here stays a raw
 * t_allocator, exactly mirroring the C signature, like every other
 * namespaced free function in this codebase. */

inline t_size	strlen(const char *__restrict__ str) FT_NOEXCEPT
{
	return (c::ft_strlen(str));
}

inline c::t_str	cstr_to_str(c::t_allocator allocator,
		const char *cstr) FT_NOEXCEPT
{
	return (c::ft_cstr_to_str(allocator, cstr));
}

}
}

#endif
