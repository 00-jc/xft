/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_HPP
# define VEC_HPP

# include "c.hpp"
# include "detail.hpp"
# include "alloc.hpp"

namespace xft
{
namespace vec
{

namespace c = xft::c;

/* Vec<T> wraps t_vec as its sole state, exactly the way the underlying
 * vec_* C API does: no allocator is stored on the side. alloc::Allocator is
 * a plain value the caller already owns (it wraps t_allocator, a
 * vtable + context pointer), so every method that the underlying
 * vec_* call needs an allocator for takes one as a parameter instead
 * of remembering one at construction, matching the C API's calling
 * convention and lifetime rules exactly (nothing here frees memory
 * implicitly; destroy() must be called by hand, precisely like
 * vec_destroy()). Every method below calls its ::ft_vec_* counterpart
 * directly - there is no free-function layer sitting in between, since
 * each one exists only to serve this class. Because t_vec is itself a
 * plain copyable struct in C, Vec<T> is left copyable too. */
template <typename T>
class Vec
{
	public:

		Vec(void) FT_NOEXCEPT
			: _raw(c::t_vec())
		{
		}

		static Vec	create(alloc::Allocator allocator,
				t_size capacity = 1) FT_NOEXCEPT
		{
			return (Vec(c::ft_vec(allocator.raw(), capacity, sizeof(T))));
		}

		void	destroy(alloc::Allocator allocator) FT_NOEXCEPT
		{
			c::ft_vec_destroy(allocator.raw(), &_raw);
		}

		bool	valid(void) const FT_NOEXCEPT
		{
			return (_raw.buf.mem != 0);
		}

		t_size	len(void) const FT_NOEXCEPT
		{
			return (c::ft_vec_len(&_raw, sizeof(T)));
		}

		t_size	capacity(void) const FT_NOEXCEPT
		{
			return (_raw.buf.size / sizeof(T));
		}

		bool	empty(void) const FT_NOEXCEPT
		{
			return (len() == 0);
		}

		void	clear(void) FT_NOEXCEPT
		{
			c::ft_vec_clear(&_raw);
		}

		/* n is elements to grow the buffer BY, not a target capacity: it
		 * mirrors vec_reserve()'s own additive semantics. */
		t_result	reserve(alloc::Allocator allocator,
				t_size additional_elements) FT_NOEXCEPT
		{
			return (c::ft_vec_reserve(allocator.raw(), &_raw,
					additional_elements * sizeof(T)));
		}

		t_result	push_back(alloc::Allocator allocator,
				const T &value) FT_NOEXCEPT
		{
			return (c::ft_vec_push_back(allocator.raw(), &_raw,
					reinterpret_cast<const t_u8 *>(&value), sizeof(T)));
		}

		t_result	extend(alloc::Allocator allocator,
				t_buffer data) FT_NOEXCEPT
		{
			return (c::ft_vec_extend(allocator.raw(), &_raw, data));
		}

		void	pop(void) FT_NOEXCEPT
		{
			c::ft_vec_pop(&_raw, sizeof(T));
		}

		t_result	popmv(T &dest) FT_NOEXCEPT
		{
			return (c::ft_vec_popmv(&_raw, &dest, sizeof(T)));
		}

		t_result	pop_managed(alloc::Allocator allocator) FT_NOEXCEPT
		{
			return (c::ft_vec_pop_managed(allocator.raw(), &_raw,
					sizeof(T)));
		}

		t_result	remove(t_size idx) FT_NOEXCEPT
		{
			return (c::ft_vec_remove(&_raw, idx, sizeof(T)));
		}

		t_result	remove_managed(alloc::Allocator allocator,
				t_size idx) FT_NOEXCEPT
		{
			return (c::ft_vec_remove_managed(allocator.raw(), &_raw, idx,
					sizeof(T)));
		}

		T	&get_mut(t_size idx) FT_NOEXCEPT
		{
			return (*static_cast<T *>(c::ft_vec_get_mut(&_raw, idx,
					sizeof(T))));
		}

		const T	&get(t_size idx) const FT_NOEXCEPT
		{
			return (*static_cast<const T *>(c::ft_vec_get(&_raw, idx,
					sizeof(T))));
		}

		T	&get_last(void) FT_NOEXCEPT
		{
			return (*static_cast<T *>(c::ft_vec_get_last(&_raw,
					sizeof(T))));
		}

		const T	&peek_last(void) const FT_NOEXCEPT
		{
			return (*static_cast<const T *>(c::ft_vec_peek_last(&_raw,
					sizeof(T))));
		}

		T	&operator[](t_size idx) FT_NOEXCEPT
		{
			return (get_mut(idx));
		}

		const T	&operator[](t_size idx) const FT_NOEXCEPT
		{
			return (get(idx));
		}

		c::t_vec	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_vec	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		explicit Vec(c::t_vec raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_vec	_raw;
};

}
}

#endif
