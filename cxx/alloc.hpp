/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_HPP
# define ALLOC_HPP

# include "c.hpp"
# include "detail.hpp"

namespace xft
{
namespace alloc
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: alloc_clone and the palloc* family
 * keep their C names, parameter order and return value, just namespaced
 * and marked FT_NOEXCEPT (none of these can throw, they report failure
 * through explicit return values). alloc_clone is a generic clone
 * callback handed around by value, not a method on any one allocator
 * instance, and palloc/palloc_resize/palloc_free are raw one-shot page
 * allocation calls with no backing struct or lifetime to attach a class
 * to - unlike gpa/reporta/arena and their alloc/realloc/free/allocator
 * families below, which fold directly into Gpa/Reporta/Arena/Allocator. */

inline t_buffer	alloc_clone(t_any self, t_buffer buffer) FT_NOEXCEPT
{
	return (c::ft_alloc_clone(self, buffer));
}

inline t_buffer	palloc(t_size size) FT_NOEXCEPT
{
	return (c::ft_palloc(size));
}

inline t_buffer	palloc_resize(t_buffer b, t_size new_size) FT_NOEXCEPT
{
	return (c::ft_palloc_resize(b, new_size));
}

inline void	palloc_free(t_buffer b) FT_NOEXCEPT
{
	c::ft_palloc_free(b);
}

/* Allocator wraps t_allocator (the vtable + context pointer struct passed
 * by value across the whole library) as its sole state: a non-owning
 * handle, exactly like the C struct it mirrors. It never stores which
 * backing Gpa/Arena/Reporta it came from beyond that struct itself. */
class Allocator
{
	public:

		explicit Allocator(c::t_allocator raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		t_buffer	allocate(t_size size, t_size align) FT_NOEXCEPT
		{
			return (_raw.vtable.allocate(_raw.allocator, size, align));
		}

		t_buffer	reallocate(t_buffer old, t_size new_size,
				t_size align) FT_NOEXCEPT
		{
			return (_raw.vtable.realloc(_raw.allocator, old, new_size,
					align));
		}

		void	free(t_buffer old) FT_NOEXCEPT
		{
			_raw.vtable.free(_raw.allocator, old);
		}

		void	destroy(void) FT_NOEXCEPT
		{
			_raw.vtable.destroy(_raw.allocator);
		}

		t_buffer	clone(t_buffer buffer) FT_NOEXCEPT
		{
			return (_raw.vtable.clone(_raw.allocator, buffer));
		}

		static Allocator	page(void) FT_NOEXCEPT
		{
			return (Allocator(c::ft_new_page_alloc()));
		}

		c::t_allocator	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_allocator	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		c::t_allocator	_raw;
};

/* Gpa wraps t_gpa (a slab-based general purpose allocator) as its sole
 * state: the class owns no allocator of its own, it *is* one. Every
 * method below calls its ::ft_gpa_* counterpart directly - there is no
 * free-function layer sitting in between, since each one exists only to
 * serve this class. */
class Gpa
{
	public:

		static Gpa	create(void) FT_NOEXCEPT
		{
			return (Gpa(c::ft_gpa()));
		}

		void	destroy(void) FT_NOEXCEPT
		{
			c::ft_gpa_destroy(&_raw);
		}

		t_buffer	alloc(t_size size, t_size align) FT_NOEXCEPT
		{
			return (c::ft_gpa_alloc(&_raw, size, align));
		}

		t_buffer	realloc(t_buffer buf, t_size newsize,
				t_size align) FT_NOEXCEPT
		{
			return (c::ft_gpa_realloc(&_raw, buf, newsize, align));
		}

		void	free(t_buffer buf) FT_NOEXCEPT
		{
			c::ft_gpa_free(&_raw, buf);
		}

		Allocator	allocator(void) FT_NOEXCEPT
		{
			return (Allocator(c::ft_gpa_allocator(&_raw)));
		}

		c::t_gpa	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_gpa	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		explicit Gpa(c::t_gpa raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_gpa	_raw;
};

/* Reporta wraps t_reporta (a Gpa that also tracks allocation stats).
 * Every method below calls its ::ft_reporta_* counterpart directly -
 * there is no free-function layer sitting in between, since each one
 * exists only to serve this class. */
class Reporta
{
	public:

		static Reporta	create(void) FT_NOEXCEPT
		{
			return (Reporta(c::ft_reporta()));
		}

		void	destroy(void) FT_NOEXCEPT
		{
			c::ft_reporta_destroy(&_raw);
		}

		t_buffer	alloc(t_size size, t_size align) FT_NOEXCEPT
		{
			return (c::ft_reporta_alloc(&_raw, size, align));
		}

		t_buffer	realloc(t_buffer buf, t_size newsize,
				t_size align) FT_NOEXCEPT
		{
			return (c::ft_reporta_realloc(&_raw, buf, newsize, align));
		}

		void	free(t_buffer buf) FT_NOEXCEPT
		{
			c::ft_reporta_free(&_raw, buf);
		}

		Allocator	allocator(void) FT_NOEXCEPT
		{
			return (Allocator(c::ft_reporta_allocator(&_raw)));
		}

		c::t_reporta	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_reporta	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		explicit Reporta(c::t_reporta raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_reporta	_raw;
};

/* Arena wraps t_arena (a bump allocator over a chain of mmap'd
 * hugepages). Every method below calls its ::ft_*arena* counterpart
 * directly - there is no free-function layer sitting in between, since
 * each one exists only to serve this class. */
class Arena
{
	public:

		static Arena	create(void) FT_NOEXCEPT
		{
			return (Arena(c::ft_new_arena_alloc()));
		}

		void	destroy(void) FT_NOEXCEPT
		{
			c::ft_destroy_arena(&_raw);
		}

		t_any	alloc(t_size size, t_size align) FT_NOEXCEPT
		{
			return (c::ft_arena_alloc(&_raw, size, align));
		}

		c::t_arena_checkpoint	checkpoint(void) const FT_NOEXCEPT
		{
			return (c::ft_arena_checkpoint(&_raw));
		}

		void	rewind_clean(c::t_arena_checkpoint cp) FT_NOEXCEPT
		{
			c::ft_arena_rewind_clean(&_raw, cp);
		}

		void	rewind(c::t_arena_checkpoint cp) FT_NOEXCEPT
		{
			c::ft_arena_rewind(&_raw, cp);
		}

		Allocator	allocator(void) FT_NOEXCEPT
		{
			return (Allocator(c::ft_arena_allocator(&_raw)));
		}

		c::t_arena	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_arena	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		explicit Arena(c::t_arena raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_arena	_raw;
};

}
}

#endif
