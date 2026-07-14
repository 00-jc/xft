/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_HPP
# define RT_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace rt
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: every function keeps its C name,
 * parameter order and return value, just namespaced and marked FT_NOEXCEPT
 * (they never unwind via C++ exceptions - _start and rt_entry
 * terminate the process/thread instead, same as the C functions they
 * wrap; FT_NOEXCEPT is the C++98 spelling of "never unwinds"). t_elf64_auxv,
 * t_auxv and t_xft_rt stay module-owned types under c:: (built once by the
 * startup code itself before main() ever runs, not something user code
 * constructs or owns through methods), exactly like the packed math
 * structs in math.h. */

# if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

inline void	_start(void) FT_NOEXCEPT
	__attribute__((__noreturn__));

inline void	_start(void) FT_NOEXCEPT
{
	c::_start();
}

inline void	rt_entry(t_any *sp) FT_NOEXCEPT
	__attribute__((__noreturn__));

inline void	rt_entry(t_any *sp) FT_NOEXCEPT
{
	c::ft_rt_entry(sp);
}

# elif defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

inline void	_start(void) FT_NOEXCEPT
	__attribute__((__noreturn__));

inline void	_start(void) FT_NOEXCEPT
{
	c::_start();
}

inline void	rt_entry(t_any *sp) FT_NOEXCEPT
	__attribute__((__noreturn__));

inline void	rt_entry(t_any *sp) FT_NOEXCEPT
{
	c::ft_rt_entry(sp);
}

# endif

inline int	main(const c::t_xft_rt *__restrict__ const rt) FT_NOEXCEPT
{
	return (c::ft_main(rt));
}

}
}

#endif
