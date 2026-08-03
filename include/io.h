/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/05 09:56:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <stdbool.h>
# include "syscalls.h"
# include "cstr.h"
# include "mem.h"
# include "alloc.h"
# include "types/io_types.h"

/// \brief Default byte capacity used where a caller does not size its own
/// staging buffer for a `t_writer`/`t_reader`.
# ifndef BUFSIZE
#  define BUFSIZE 4096
# endif

/// \brief Copy \p buf into a writer's staging buffer, draining through the
/// writer's vtable (`drain`) whenever it does not fit.
/// \param writer Writer to append to; its staging buffer (`writer->buffer`)
/// must already be backed by memory.
/// \param buf Bytes to write; ownership is not taken, the data is copied
/// (either into the staging buffer or handed to `drain` synchronously).
/// \return `OK` on success, `KO` if the underlying drain fails (e.g. a
/// `-1`/short `writev`, or the raw sink running out of capacity).
/// \note When \p buf does not fit in the remaining staging space, the
/// pending buffered bytes and the new data are drained together as two
/// iovecs, and any leftover tail is copied back into the now-empty buffer.
t_result		ft_writer_write(t_writer *__restrict__ const writer,\
					t_buffer buf)\
					__attribute__((__nonnull__(1)));

/// \brief Build a `t_writer` that flushes/drains to a file descriptor via
/// `ft_write`/`ft_writev`.
/// \param buffer Caller-owned staging buffer; must outlive the writer.
/// \param fd File descriptor writes are issued against.
/// \return An initialized, empty (`end == 0`) `t_writer`.
t_writer		ft_get_fs_writer(t_buffer buffer, t_i32 fd)\
					__attribute__((const));

/// \brief Build a `t_reader` that fills from a file descriptor via
/// `ft_read`.
/// \param buffer Caller-owned staging buffer; must outlive the reader.
/// \param fd File descriptor reads are issued against.
/// \return An initialized, empty (`end == valid == 0`) `t_reader`.
t_reader		ft_get_fs_reader(t_buffer buffer, t_i32 fd)\
					__attribute__((const, __always_inline__));

/// \brief Read exactly up to \p len bytes into \p dst, buffering through
/// \p reader when \p len is smaller than the reader's staging buffer, or
/// bypassing it (an unbuffered fill) when \p len is at least as large.
/// \param reader Reader to pull from.
/// \param dst Destination for the bytes read; must hold at least \p len
/// bytes.
/// \param len Number of bytes requested.
/// \param total Out param: number of bytes actually copied into \p dst.
/// Can be less than \p len on EOF (a zero-byte underlying read), never on
/// error.
/// \return `OK` on success (including a short read caused by EOF), `KO` if
/// the underlying fill fails.
t_result		ft_read_from_reader(t_reader *reader,
					t_u8 *dst, const t_size len, t_size *total)\
					__attribute__((__nonnull__(1, 2, 4)));

/// \brief Flush any buffered bytes still pending in \p writer via its
/// vtable's `flush` (a synchronous, blocking write loop for fd-backed
/// writers).
/// \param writer Writer to flush.
/// \return `OK` on success, `KO` if the underlying write fails.
t_result		ft_writer_flush(t_writer *__restrict__ const writer)\
					__attribute__((__nonnull__(1)));

/// \brief Build a `t_writer` that drains into an external in-memory buffer
/// instead of a file descriptor.
/// \param buffer Caller-owned staging buffer; must outlive the writer.
/// \param external Destination memory the writer copies into on drain/flush;
/// must outlive the writer and hold at least \p external_valid bytes.
/// \param external_valid Capacity, in bytes, of \p external. Drains that
/// would exceed the remaining capacity fail with `KO`.
/// \return An initialized, empty `t_writer` with `external_size` (bytes
/// written so far) starting at 0.
t_writer		ft_get_raw_writer(t_buffer buffer,\
					t_u8 *__restrict__ const external, t_size external_valid)\
					__attribute__((const));

/// \brief Build a `t_reader` that fills from an external in-memory buffer
/// instead of a file descriptor.
/// \param buffer Caller-owned staging buffer; must outlive the reader.
/// \param external Source data to read from; must outlive the reader.
/// \return An initialized, empty `t_reader` with `drained` (bytes consumed
/// from \p external so far) starting at 0.
t_reader		ft_get_raw_reader(t_buffer buffer, t_buffer external)\
					__attribute__((const));

/// \brief Fixed file descriptor constants (`STDERR_FILENO`/`STDIN_FILENO`/
/// `STDOUT_FILENO`), exposed as functions rather than macros for ABI/inline
/// consistency with the rest of the module.
t_i32			ft_get_stderr(void)\
					__attribute__((const));
t_i32			ft_get_stdin(void)\
					__attribute__((const));
t_i32			ft_get_stdout(void)\
					__attribute__((const));

/// \brief Map an entire regular file read-only into memory: `ft_stat` for
/// its size, `ft_open` with \p flags, `ft_fmap` the whole extent, then close
/// the descriptor (the mapping outlives the fd).
/// \param name NUL-terminated path to the file.
/// \param flags Flags forwarded to `ft_open` (e.g. `O_RDONLY`).
/// \return The mapped `t_buffer` (`.mem` = mapping base, `.size` = file
/// size) on success; a zeroed `t_buffer` (`.mem == nullptr`) if `stat`,
/// `open`, or the mmap itself fails.
/// \note Caller must release the mapping with `ft_unmap_file`.
t_buffer		ft_map_file(const t_u8 *__restrict__ const name,\
					t_u32 flags)\
					__attribute__((__nonnull__(1)));

/// \brief Unmap a `t_buffer` previously returned by `ft_map_file`.
/// \param file Buffer to unmap; `.mem`/`.size` are passed straight to
/// `ft_munmap`.
void			ft_unmap_file(t_buffer file);

#endif
