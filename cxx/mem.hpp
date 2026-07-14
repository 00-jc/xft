/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_HPP
# define MEM_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace mem
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: every function keeps its C name, parameter
 * order and return value, just namespaced and marked FT_NOEXCEPT (none of
 * these can throw, they report failure through explicit return values;
 * FT_NOEXCEPT is the C++98 spelling of "this function never unwinds").
 * These are plain pointer/size operations with no owning object or
 * lifetime of their own, so there is no class to fold them into - unlike
 * fatptr, which builds the one struct (t_buffer) this header actually
 * wraps in a class and so folds directly into Buffer below. */

inline void	bzero(t_any ptr, t_size n) FT_NOEXCEPT
{
	c::ft_bzero(ptr, n);
}

inline void	memset(t_any s, const t_u8 c, t_size n) FT_NOEXCEPT
{
	xft::c::ft_memset(s, c, n);
}

inline void	memcpy(t_any dest, t_cany src, t_size n) FT_NOEXCEPT
{
	c::ft_memcpy(dest, src, n);
}

inline void	memtake(t_any dest, t_any src, t_size n) FT_NOEXCEPT
{
	c::ft_memtake(dest, src, n);
}

inline void	memmove(t_any dest, t_cany src, t_size n) FT_NOEXCEPT
{
	c::ft_memmove(dest, src, n);
}

inline t_any	memchr(t_cany ptr, int c, t_size n) FT_NOEXCEPT
{
	return (xft::c::ft_memchr(ptr, c, n));
}

inline t_ssize	memcmp(t_cany dest, t_cany src, t_size n) FT_NOEXCEPT
{
	return (c::ft_memcmp(dest, src, n));
}

inline void	membroadcast(t_any dst, t_any src, t_size chunks,
		t_size n) FT_NOEXCEPT
{
	c::ft_membroadcast(dst, src, chunks, n);
}

inline void	prefetch0(t_cany ptr, t_size size) FT_NOEXCEPT
{
	c::ft_prefetch0(ptr, size);
}

inline void	prefetch1(t_cany ptr, t_size size) FT_NOEXCEPT
{
	c::ft_prefetch1(ptr, size);
}

inline void	prefetch2(t_cany ptr, t_size size) FT_NOEXCEPT
{
	c::ft_prefetch2(ptr, size);
}

inline void	prefetchnta(t_cany ptr, t_size size) FT_NOEXCEPT
{
	c::ft_prefetchnta(ptr, size);
}

inline t_any	overlap(t_cany ptr, t_size chunk_size,
		t_size rem_size) FT_NOEXCEPT
{
	return (c::ft_overlap(ptr, chunk_size, rem_size));
}

inline t_any	align_fwd(t_any ptr, const t_size align) FT_NOEXCEPT
{
	return (c::ft_align_fwd(ptr, align));
}

inline t_any	align_bkw(t_any ptr, const t_size align) FT_NOEXCEPT
{
	return (c::ft_align_bkw(ptr, align));
}

inline void	stfence(void) FT_NOEXCEPT
{
	c::ft_stfence();
}

inline void	ldfence(void) FT_NOEXCEPT
{
	c::ft_ldfence();
}

/* Buffer wraps t_buffer (the fat-pointer struct used across the whole
 * library) as its sole piece of state: a non-owning view, exactly like
 * the C struct it mirrors. fatptr() calls ::ft_fatptr directly rather
 * than through a free-function wrapper, since building a t_buffer is
 * squarely this class's job. */
class Buffer
{
	public:

		Buffer(void) FT_NOEXCEPT
			: _raw(t_buffer())
		{
		}

		explicit Buffer(t_buffer raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		static Buffer	fatptr(c::t_blk8r mem, t_size size) FT_NOEXCEPT
		{
			return (Buffer(c::ft_fatptr(mem, size)));
		}

		t_size	size(void) const FT_NOEXCEPT
		{
			return (_raw.size);
		}

		t_u8	*data(void) FT_NOEXCEPT
		{
			return (_raw.mem);
		}

		const t_u8	*data(void) const FT_NOEXCEPT
		{
			return (_raw.mem);
		}

		t_buffer	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const t_buffer	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		t_buffer	_raw;
};

}
}

#endif
