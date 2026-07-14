/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuzzer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUZZER_HPP
# define FUZZER_HPP

# include "c.hpp"
# include "detail.hpp"
# include "alloc.hpp"

namespace xft
{
namespace fuzzer
{

namespace c = xft::c;

/* Fuzzer wraps t_fuzzer (xoshiro state, an embedded t_arena, generated
 * buffers, and the last generated value) as its sole state. The arena
 * is carried by value inside t_fuzzer itself (not referenced through an
 * allocator interface), so create() takes an alloc::Arena - the nicer
 * C++ wrapper - only at this class boundary and unwraps it via raw()
 * once. Every method below calls its ::ft_fuzz* counterpart directly -
 * there is no free-function layer sitting in between, since each one
 * exists only to serve this class. */
class Fuzzer
{
	public:

		Fuzzer(void) FT_NOEXCEPT
			: _raw(c::t_fuzzer())
		{
		}

		static Fuzzer	create(alloc::Arena arena) FT_NOEXCEPT
		{
			return (Fuzzer(c::ft_fuzzer_new(arena.raw())));
		}

		t_result	add_rand(void) FT_NOEXCEPT
		{
			return (c::ft_fuzzer_add_rand(&_raw));
		}

		t_buffer	*rand_buffer(void) FT_NOEXCEPT
		{
			return (c::ft_fuzz_get_rand(&_raw));
		}

		t_u64a	rand_u(void) FT_NOEXCEPT
		{
			return (c::ft_fuzz_get_rand_u(&_raw));
		}

		t_f64	rand_d(void) FT_NOEXCEPT
		{
			return (c::ft_fuzz_get_rand_d(&_raw));
		}

		void	destroy(void) FT_NOEXCEPT
		{
			c::ft_fuzzer_destroy(&_raw);
		}

		c::t_fuzzer	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_fuzzer	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		explicit Fuzzer(c::t_fuzzer raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_fuzzer	_raw;
};

}
}

#endif
