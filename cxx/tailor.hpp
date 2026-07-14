/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tailor.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAILOR_HPP
# define TAILOR_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace tailor
{

namespace c = xft::c;

/* Tailor wraps t_tailor (arena, perf counters, timings, buffers,
 * checkpoint, writer) as its sole state, exactly the way the underlying
 * tailor_* C API does: no allocator is stored on the side beyond what
 * is already embedded in t_tailor itself. init() replaces the C pattern
 * of declaring a t_tailor and calling tailor_new() on its address;
 * nothing here opens counters or maps buffers implicitly, and destroy()
 * must still be called by hand, precisely like tailor_destroy(). Every
 * method below calls its ::ft_* counterpart directly - there is no
 * free-function layer sitting in between, since each one exists only to
 * serve this class. t_tailor_bench stays a module-owned type under c::
 * (an array element handed to bench(), like items pushed into a Vec<T>,
 * not a singular thing to wrap). */
class Tailor
{
	public:

		Tailor(void) FT_NOEXCEPT
			: _raw(c::t_tailor())
		{
		}

		t_result	init(t_f64 warmup_sec, t_u64a min_samples) FT_NOEXCEPT
		{
			return (c::ft_tailor_new(&_raw, warmup_sec, min_samples));
		}

		t_result	bench(c::t_tailor_bench benches[], t_size size) FT_NOEXCEPT
		{
			return (c::ft_tailor_bench(&_raw, benches, size));
		}

		t_result	buffers(t_size *sizes, t_u8 *alignment,
				t_size n) FT_NOEXCEPT
		{
			return (c::ft_tailor_buffers(&_raw, sizes, alignment, n));
		}

		void	destroy(void) FT_NOEXCEPT
		{
			c::ft_tailor_destroy(&_raw);
		}

		t_size	count(void) FT_NOEXCEPT
		{
			return (c::ft_tailor_getcount(&_raw));
		}

		t_buffer	random_buffer(void) FT_NOEXCEPT
		{
			return (c::ft_get_random_buffer(&_raw));
		}

		t_buffer	*all_buffers(t_size *n) FT_NOEXCEPT
		{
			return (c::ft_get_all_buffers(&_raw, n));
		}

		void	add_processed_bytes(t_size bytes) FT_NOEXCEPT
		{
			c::ft_tailor_add_processed_bytes(&_raw, bytes);
		}

		t_size	random_num(void) FT_NOEXCEPT
		{
			return (c::ft_tailor_get_random_num(&_raw));
		}

		c::t_tailor	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_tailor	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		c::t_tailor	_raw;
};

}
}

#endif
