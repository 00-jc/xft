/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomics.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOMICS_HPP
# define ATOMICS_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace atomics
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: thread_fence and signal_fence keep
 * their C names, parameter and return behaviour, just namespaced and
 * marked FT_NOEXCEPT (neither can throw; FT_NOEXCEPT is the C++98
 * spelling of "never unwinds"). Both operate process/thread-wide with
 * no owning object, so they stay free functions here - unlike
 * mutex_lock/mutex_unlock/mutex_init below, which fold directly into
 * Mutex. */

inline void	thread_fence(t_i32a memorder) FT_NOEXCEPT
{
	c::ft_thread_fence(memorder);
}

inline void	signal_fence(t_i32a memorder) FT_NOEXCEPT
{
	c::ft_signal_fence(memorder);
}

/* Mutex wraps t_mutex (a volatile t_i32a futex word) as its sole state.
 * The default constructor only zeroes the word; init() must still be
 * called by hand to bring it to FT_UNLOCKED, exactly mirroring the C
 * flow of declaring a t_mutex and calling mutex_init() on it before
 * the first lock()/unlock() - nothing here happens implicitly. Every
 * method below calls its ::ft_mutex_* counterpart directly - there is
 * no free-function layer sitting in between, since each one exists
 * only to serve this class. */
class Mutex
{
	public:

		Mutex(void) FT_NOEXCEPT
			: _raw(0)
		{
		}

		void	init(void) FT_NOEXCEPT
		{
			c::ft_mutex_init(&_raw);
		}

		void	lock(c::t_mutex_type type) FT_NOEXCEPT
		{
			c::ft_mutex_lock(&_raw, type);
		}

		void	unlock(void) FT_NOEXCEPT
		{
			c::ft_mutex_unlock(&_raw);
		}

		c::t_mutex	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_mutex	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		c::t_mutex	_raw;
};

}
}

#endif
