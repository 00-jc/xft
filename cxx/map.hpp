/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "c.hpp"
# include "detail.hpp"
# include "alloc.hpp"

namespace xft
{
namespace map
{

namespace c = xft::c;

/* Map<T> wraps t_map as its sole state, exactly the way the underlying
 * map_* C API does: no allocator is stored on the side. alloc::Allocator
 * is a plain value the caller already owns, so every method that the
 * underlying map_* call needs an allocator for takes one as a
 * parameter instead of remembering one at construction, matching the C
 * API's calling convention and lifetime rules exactly (nothing here
 * frees memory implicitly; destroy() must be called by hand, precisely
 * like map_destroy()). T is the pointee type of the values stored in
 * the map: the C map stores an opaque t_u8 * per key, this just adds
 * the cast back to T * at the edges. Every method below calls its
 * ::ft_map_* counterpart directly - there is no free-function layer
 * sitting in between, since each one exists only to serve this class.
 * Because t_map is itself a plain copyable struct in C, Map<T> is left
 * copyable too. */
template <typename T>
class Map
{
	public:

		Map(void) FT_NOEXCEPT
			: _raw(c::t_map())
		{
		}

		static Map	create(alloc::Allocator allocator) FT_NOEXCEPT
		{
			return (Map(c::ft_map_new(allocator.raw())));
		}

		static Map	with(alloc::Allocator allocator,
				t_size capacity) FT_NOEXCEPT
		{
			return (Map(c::ft_map_with(allocator.raw(), capacity)));
		}

		void	destroy(alloc::Allocator allocator) FT_NOEXCEPT
		{
			c::ft_map_destroy(allocator.raw(), &_raw);
		}

		t_size	count(void) const FT_NOEXCEPT
		{
			return (_raw.count);
		}

		t_size	table_size(void) const FT_NOEXCEPT
		{
			return (_raw.table_size);
		}

		bool	empty(void) const FT_NOEXCEPT
		{
			return (count() == 0);
		}

		T	*lookup(t_buffer key) const FT_NOEXCEPT
		{
			return (static_cast<T *>(c::ft_map_lookup(&_raw, key)));
		}

		t_result	insert(alloc::Allocator allocator, t_buffer key,
				T *value) FT_NOEXCEPT
		{
			return (c::ft_map_insert(allocator.raw(), &_raw, key,
					reinterpret_cast<t_u8 *>(value)));
		}

		/* named erase() rather than delete(): delete is a reserved
		 * C++ keyword and cannot be used as a member function name. */
		void	erase(t_buffer key) FT_NOEXCEPT
		{
			c::ft_map_delete(&_raw, key);
		}

		void	clear(void) FT_NOEXCEPT
		{
			c::ft_map_clear(&_raw);
		}

		c::t_map	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_map	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		explicit Map(c::t_map raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_map	_raw;
};

}
}

#endif
