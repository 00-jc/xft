/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERF_HPP
# define PERF_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace perf
{

namespace c = xft::c;

/* thin, exact-semantics wrapper: bind_process_to_cpu keeps its C name,
 * parameter order and return value, just namespaced and marked
 * FT_NOEXCEPT (it cannot throw, it reports failure through its explicit
 * return value; FT_NOEXCEPT is the C++98 spelling of "never unwinds").
 * It has no owning object to attach to (it affects process-wide CPU
 * affinity, not any one t_perf_counters), so it stays a free function
 * here - unlike perf_create_counters/perf_counters_reset/
 * perf_counters_start/perf_counters_stop/perf_start_sample/
 * perf_collect_sample/perf_destroy_counters below, which fold directly
 * into PerfCounters. */

inline t_result	bind_process_to_cpu(t_u32 cpu) FT_NOEXCEPT
{
	return (c::ft_bind_process_to_cpu(cpu));
}

/* PerfCounters wraps t_perf_counters (an array typedef of 9 longs, the
 * open perf_event file descriptors) as its sole state. Like t_xoshiro in
 * rng.hpp, an array typedef cannot be value-initialized via a
 * mem-initializer list in C++98, so the default constructor zeroes it
 * by hand in the body. This mirrors the C flow exactly: declare the
 * state, call create() once to open the counters, reset()/start()/
 * stop() around the region being measured, start_sample()/sample() to
 * read it, and destroy() once done - nothing here opens or closes file
 * descriptors implicitly. Every method below calls its ::ft_perf_*
 * counterpart directly - there is no free-function layer sitting in
 * between, since each one exists only to serve this class. raw()
 * returns a pointer to the whole underlying array (t_perf_counters *),
 * not a decayed long *. */
class PerfCounters
{
	public:

		PerfCounters(void) FT_NOEXCEPT
		{
			t_size	i;

			i = 0;
			while (i < 9)
			{
				_raw[i] = 0;
				i = i + 1;
			}
		}

		t_result	create(void) FT_NOEXCEPT
		{
			return (c::ft_perf_create_counters(_raw));
		}

		void	reset(void) FT_NOEXCEPT
		{
			c::ft_perf_counters_reset(_raw);
		}

		void	start(void) FT_NOEXCEPT
		{
			c::ft_perf_counters_start(_raw);
		}

		void	stop(void) FT_NOEXCEPT
		{
			c::ft_perf_counters_stop(_raw);
		}

		void	start_sample(c::t_perf_sample &s) FT_NOEXCEPT
		{
			c::ft_perf_start_sample(_raw, &s);
		}

		t_result	sample(t_size n, c::t_perf_sample &s) FT_NOEXCEPT
		{
			return (c::ft_perf_collect_sample(n, _raw, &s));
		}

		void	destroy(void) FT_NOEXCEPT
		{
			c::ft_perf_destroy_counters(_raw);
		}

		c::t_perf_counters	*raw(void) FT_NOEXCEPT
		{
			return (&_raw);
		}

		const c::t_perf_counters	*raw(void) const FT_NOEXCEPT
		{
			return (&_raw);
		}

	private:

		c::t_perf_counters	_raw;
};

}
}

#endif
