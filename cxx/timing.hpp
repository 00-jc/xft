/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMING_HPP
# define TIMING_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace timing
{

namespace c = xft::c;

/* thin, exact-semantics wrapper: get_nanos keeps its C name and
 * return value, just namespaced and marked FT_NOEXCEPT (it cannot throw;
 * FT_NOEXCEPT is the C++98 spelling of "never unwinds"). timing.h has no
 * struct to wrap: it is a single free function reading the system
 * clock, so there is no class to attach it to. */

inline t_u64a	get_nanos(void) FT_NOEXCEPT
{
	return (c::ft_get_nanos());
}

}
}

#endif
