/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_HPP
# define STR_HPP

# include "c.hpp"
# include "detail.hpp"
# include "alloc.hpp"

namespace xft
{
namespace str
{

namespace c = xft::c;

/* Str wraps t_str as its sole state, exactly the way the underlying
 * str_* C API does: no allocator is stored on the side. alloc::Allocator
 * is a plain value the caller already owns, so every method that the
 * underlying str_* call needs an allocator for takes one as a
 * parameter instead of remembering one at construction, matching the C
 * API's calling convention and lifetime rules exactly (nothing here
 * frees memory implicitly; destroy() must be called by hand, precisely
 * like str_destroy()). Every method below calls its ::ft_str_*
 * counterpart directly - there is no free-function layer sitting in
 * between, since each one exists only to serve this class. Because
 * t_str is itself a plain copyable struct in C, Str is left copyable
 * too. */
class Str
{
	public:

		Str(void) FT_NOEXCEPT
			: _raw(c::t_str())
		{
		}

		static Str	create(alloc::Allocator allocator, t_size size) FT_NOEXCEPT
		{
			return (Str(c::ft_str(allocator.raw(), size)));
		}

		void	destroy(alloc::Allocator allocator) FT_NOEXCEPT
		{
			c::ft_str_destroy(allocator.raw(), &_raw);
		}

		bool	valid(void) const FT_NOEXCEPT
		{
			return (_raw.mem != 0);
		}

		t_size	size(void) const FT_NOEXCEPT
		{
			return (_raw.size);
		}

		t_size	capacity(void) const FT_NOEXCEPT
		{
			return (_raw.capacity);
		}

		bool	empty(void) const FT_NOEXCEPT
		{
			return (size() == 0);
		}

		t_u8	*data(void) FT_NOEXCEPT
		{
			return (_raw.mem);
		}

		const t_u8	*data(void) const FT_NOEXCEPT
		{
			return (_raw.mem);
		}

		t_result	reserve(alloc::Allocator allocator, t_size n) FT_NOEXCEPT
		{
			return (c::ft_str_reserve(allocator.raw(), &_raw, n));
		}

		t_result	extend(alloc::Allocator allocator, const t_u8 *mem,
				t_size n) FT_NOEXCEPT
		{
			return (c::ft_str_extend(allocator.raw(), &_raw, mem, n));
		}

		t_result	push_back(alloc::Allocator allocator,
				const t_u8 byte) FT_NOEXCEPT
		{
			return (c::ft_str_push_back(allocator.raw(), &_raw, byte));
		}

		t_result	remove(t_size i) FT_NOEXCEPT
		{
			return (c::ft_str_remove(&_raw, i));
		}

		c::t_str	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_str	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		explicit Str(c::t_str raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_str	_raw;
};

}
}

#endif
