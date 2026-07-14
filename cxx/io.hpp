/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_HPP
# define IO_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace io
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: get_std{err,in,out} and map_file/
 * unmap_file keep their C names, parameter order and return value, just
 * namespaced and marked FT_NOEXCEPT (none of these can throw, they report
 * failure through explicit return values; FT_NOEXCEPT is the C++98
 * spelling of "never unwinds"). These have no owning object or lifetime
 * to attach to (plain fd getters and a one-shot mmap/munmap pair), so
 * they stay free functions here - unlike writer_write/writer_flush/
 * get_fs_writer/get_raw_writer/get_fs_reader/get_raw_reader/
 * read_from_reader below, which fold directly into Writer/Reader. */

inline t_i32	get_stderr(void) FT_NOEXCEPT
{
	return (c::ft_get_stderr());
}

inline t_i32	get_stdin(void) FT_NOEXCEPT
{
	return (c::ft_get_stdin());
}

inline t_i32	get_stdout(void) FT_NOEXCEPT
{
	return (c::ft_get_stdout());
}

inline t_buffer	map_file(const t_u8 *__restrict__ const name,
		t_u32 flags) FT_NOEXCEPT
{
	return (c::ft_map_file(name, flags));
}

inline void	unmap_file(t_buffer file) FT_NOEXCEPT
{
	c::ft_unmap_file(file);
}

/* Writer wraps t_writer (vtable, buffer, end, union-context) as its
 * sole state: the vtable and context are fully built by the fs()/
 * memory() factories, so there is no allocator anywhere to store or
 * pass. Every method below calls its ::ft_* counterpart directly - there
 * is no free-function layer sitting in between, since each one exists
 * only to serve this class. Because t_writer is itself a plain
 * copyable struct in C, Writer is left copyable too. */
class Writer
{
	public:

		Writer(void) FT_NOEXCEPT
			: _raw(c::t_writer())
		{
		}

		static Writer	fs(t_buffer buffer, t_i32 fd) FT_NOEXCEPT
		{
			return (Writer(c::ft_get_fs_writer(buffer, fd)));
		}

		static Writer	memory(t_buffer buffer, t_u8 *external,
				t_size external_valid) FT_NOEXCEPT
		{
			return (Writer(c::ft_get_raw_writer(buffer, external,
					external_valid)));
		}

		t_result	write(t_buffer buf) FT_NOEXCEPT
		{
			return (c::ft_writer_write(&_raw, buf));
		}

		t_result	flush(void) FT_NOEXCEPT
		{
			return (c::ft_writer_flush(&_raw));
		}

		c::t_writer	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_writer	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		explicit Writer(c::t_writer raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_writer	_raw;
};

/* Reader wraps t_reader (vtable, buffer, end, valid, union-context) as
 * its sole state, mirroring Writer above: fs()/memory() build the
 * vtable and context fully, no allocator involved anywhere. */
class Reader
{
	public:

		Reader(void) FT_NOEXCEPT
			: _raw(c::t_reader())
		{
		}

		static Reader	fs(t_buffer buffer, t_i32 fd) FT_NOEXCEPT
		{
			return (Reader(c::ft_get_fs_reader(buffer, fd)));
		}

		static Reader	memory(t_buffer buffer, t_buffer external) FT_NOEXCEPT
		{
			return (Reader(c::ft_get_raw_reader(buffer, external)));
		}

		t_result	read(t_u8 *dst, t_size len, t_size *total) FT_NOEXCEPT
		{
			return (c::ft_read_from_reader(&_raw, dst, len, total));
		}

		c::t_reader	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_reader	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		explicit Reader(c::t_reader raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_reader	_raw;
};

}
}

#endif
