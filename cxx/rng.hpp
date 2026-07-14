/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rng.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RNG_HPP
# define RNG_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace rng
{

namespace c = xft::c;

/* Xoshiro wraps t_xoshiro (a 4-word PRNG state array) as its sole state.
 * t_xoshiro is a C array typedef, not a struct, so unlike Vec/Str/Map it
 * cannot be value-initialized via a mem-initializer list in C++98; the
 * default constructor zeroes it by hand in the body instead. This
 * mirrors the C usage pattern exactly: declare the state, call seed()
 * once (wraps ::ft_xoshiro_init), then next() repeatedly (wraps
 * ::ft_xoshiro256ss) - nothing here seeds implicitly. Both methods call
 * their ::ft_* counterpart directly - there is no free-function layer
 * sitting in between, since each one exists only to serve this class. */
class Xoshiro
{
	public:

		Xoshiro(void) FT_NOEXCEPT
		{
			_raw[0] = 0;
			_raw[1] = 0;
			_raw[2] = 0;
			_raw[3] = 0;
		}

		void	seed(void) FT_NOEXCEPT
		{
			c::ft_xoshiro_init(_raw);
		}

		t_u64a	next(void) FT_NOEXCEPT
		{
			return (c::ft_xoshiro256ss(_raw));
		}

		t_u64a	*raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const t_u64a	*raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		c::t_xoshiro	_raw;
};

}
}

#endif
