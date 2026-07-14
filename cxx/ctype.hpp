/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctype.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTYPE_HPP
# define CTYPE_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace ctype
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: every function keeps its C name, parameter
 * order and return value, just namespaced and marked FT_NOEXCEPT (none of
 * these can throw, they report failure through explicit return values;
 * FT_NOEXCEPT is the C++98 spelling of "never unwinds"). ctype.h has no
 * struct to wrap: every function here is a pure predicate on an int, so
 * there is no class to attach them to, exactly like hash.h. Each parameter
 * below is itself named c, shadowing the c:: namespace alias inside the
 * function body, so the calls below reach the alias through its full
 * xft::c:: spelling instead. */

inline int	isalpha(int c) FT_NOEXCEPT
{
	return (xft::c::ft_isalpha(c));
}

inline int	isdigit(int c) FT_NOEXCEPT
{
	return (xft::c::ft_isdigit(c));
}

inline int	isalnum(int c) FT_NOEXCEPT
{
	return (xft::c::ft_isalnum(c));
}

inline int	isascii(int c) FT_NOEXCEPT
{
	return (xft::c::ft_isascii(c));
}

inline int	isxdigit(int c) FT_NOEXCEPT
{
	return (xft::c::ft_isxdigit(c));
}

inline int	isprint(int c) FT_NOEXCEPT
{
	return (xft::c::ft_isprint(c));
}

inline int	isspace(int c) FT_NOEXCEPT
{
	return (xft::c::ft_isspace(c));
}

}
}

#endif
