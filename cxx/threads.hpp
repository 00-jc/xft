/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/14 02:03:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_HPP
# define THREADS_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace threads
{

namespace c = xft::c;

/* ThreadCompletion wraps t_thread_completion (completion stage,
 * child_tid, parent_tid, mapped stack) as its sole state: the one
 * struct threads.h actually operates on through a function, mirroring
 * Token/Buffer above in mem.hpp/tokenizer.hpp - a plain view with
 * accessors, since there is no allocator or lifetime of its own beyond
 * the mapped stack it points at. free_exit() calls ::ft_thread_free_exit
 * directly rather than through a free-function wrapper, since that
 * function exists only to serve this class; it never unwinds via C++
 * exceptions and never returns either - it terminates the calling
 * thread instead, same as the C function it wraps - so it keeps the
 * noreturn attribute the C declaration carries. Declaring it inside the
 * class and defining it out of line mirrors how noreturn free functions
 * are split elsewhere in this codebase (attribute on the first
 * declaration, body afterwards). */
class ThreadCompletion
{
	public:

		ThreadCompletion(void) FT_NOEXCEPT
			: _raw(c::t_thread_completion())
		{
		}

		explicit ThreadCompletion(c::t_thread_completion raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_thread_completion_stage	completion(void) const FT_NOEXCEPT
		{
			return (_raw.completion);
		}

		t_i32a	child_tid(void) const FT_NOEXCEPT
		{
			return (_raw.child_tid);
		}

		t_i32a	parent_tid(void) const FT_NOEXCEPT
		{
			return (_raw.parent_tid);
		}

		t_buffer	mapped(void) const FT_NOEXCEPT
		{
			return (_raw.mapped);
		}

		void	free_exit(void) FT_NOEXCEPT
			__attribute__((__noreturn__));

		c::t_thread_completion	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_thread_completion	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		c::t_thread_completion	_raw;
};

inline void	ThreadCompletion::free_exit(void) FT_NOEXCEPT
{
	c::ft_thread_free_exit(&_raw);
}

/* Thread wraps t_thread (handle + tls_id + a pointer into the child's
 * own mapped stack where its t_thread_completion lives) as its sole
 * state, exactly the way the underlying ft_thread_* C API does: the
 * struct is a non-owning handle onto a running child, and the stack it
 * refers to is owned by that child, not by this object - nothing here
 * unmaps anything implicitly. Every method below calls its
 * ::ft_thread_* counterpart directly, since each one exists only to
 * serve this class. spawn() is a mutating method returning t_result
 * rather than a static create() factory like Map/Vec: the C spawn
 * reports failure through its return value while filling the handle
 * through an out-parameter, so the two cannot be folded into a single
 * by-value return. It takes the t_thread_arg by value (the C call takes
 * a pointer but copies *arg into the child's instance before returning,
 * so the argument never needs to outlive the call) and defaults
 * stack_size to FT_THREAD_STACKSIZE, matching the macro threads.h
 * hands callers. Because t_thread is itself a plain copyable struct in
 * C, Thread is left copyable too. */
class Thread
{
	public:

		Thread(void) FT_NOEXCEPT
			: _raw(c::t_thread())
		{
		}

		explicit Thread(c::t_thread raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		t_result	spawn(const c::t_xft_rt *__restrict__ const rt_info,
				c::t_thread_arg arg,
				t_size stack_size = FT_THREAD_STACKSIZE) FT_NOEXCEPT
		{
			return (c::ft_thread_spawn(rt_info, &_raw, &arg, stack_size));
		}

		t_result	join(void) FT_NOEXCEPT
		{
			return (c::ft_thread_join(&_raw));
		}

		void	detach(void) FT_NOEXCEPT
		{
			c::ft_thread_detach(&_raw);
		}

		c::t_thread_handle	handle(void) const FT_NOEXCEPT
		{
			return (_raw.handle);
		}

		c::t_tls_id	tls_id(void) const FT_NOEXCEPT
		{
			return (_raw.tls_id);
		}

		c::t_thread_completion	*completion(void) const FT_NOEXCEPT
		{
			return (_raw.completion);
		}

		c::t_thread	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_thread	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		c::t_thread	_raw;
};

}
}

#endif
