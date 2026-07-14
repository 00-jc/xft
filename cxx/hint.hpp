/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hint.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HINT_HPP
# define HINT_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace hint
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: every function keeps its C name, parameter
 * order and return value, just namespaced and marked FT_NOEXCEPT (none of
 * these can throw; FT_NOEXCEPT is the C++98 spelling of "never unwinds").
 * hint.h has no struct to wrap: every function here is a compiler hint with
 * no state of its own, so there is no class to attach them to, exactly like
 * hash.h. */

inline void	pin_invariant(int res) FT_NOEXCEPT
{
	c::ft_pin_invariant(res);
}

inline void	pin_invariant_msg(int res, t_buffer msg) FT_NOEXCEPT
{
	c::ft_pin_invariant_msg(res, msg);
}

inline void	assume(bool expr) FT_NOEXCEPT
{
	c::ft_assume(expr);
}

}
}

#endif
