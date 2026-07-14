/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_HPP
# define SIGNALS_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace signals
{

namespace c = xft::c;

/* thin, exact-semantics wrapper: sigfillset keeps its C name and
 * return value, just namespaced and marked FT_NOEXCEPT (it cannot throw;
 * FT_NOEXCEPT is the C++98 spelling of "never unwinds"). t_sigset is a
 * plain bitmask value type (either sigset_t or a raw t_u64a), but it is
 * module-owned rather than a primitive.h type, so it lives under c:: like
 * every other signals.h struct. The FT_SIG.../FT_BLOCK/FT_UNBLOCK/
 * FT_SETMASK macros stay plain macros: they are ordinary integer constants
 * passed as arguments, not symbols that need a namespace of their own.
 * There is no struct to wrap here, so there is no class to attach this
 * function to, exactly like hash.h. */

inline c::t_sigset	sigfillset(void) FT_NOEXCEPT
{
	return (c::ft_sigfillset());
}

}
}

#endif
