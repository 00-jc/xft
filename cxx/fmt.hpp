/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FMT_HPP
# define FMT_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace fmt
{

namespace c = xft::c;

/* thin, exact-semantics wrapper: fmt_writer keeps its C name, parameter
 * order and return value, just namespaced and marked FT_NOEXCEPT (it
 * cannot throw, it reports failure through its explicit return value;
 * FT_NOEXCEPT is the C++98 spelling of "never unwinds"). fmt.h has no
 * struct of its own to wrap - it formats into an existing t_writer
 * defined over in io.h/io.hpp - so there is no class here to fold this
 * into, exactly like hash.h. */

inline t_result	fmt_writer(c::t_writer *writer, t_buffer format,
		t_u64 *values) FT_NOEXCEPT
{
	return (c::ft_fmt_writer(writer, format, values));
}

}
}

#endif
