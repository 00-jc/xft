/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf8_idents.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/fmt.h>
#include <xft/xft.h>

// lists the UAX #31 identifiers of a UTF-8 file, one per line as
// "offset<TAB>codepoints<TAB>bytes<TAB>text", and reports every byte that
// does not decode. the file is scanned in place from its mapping:
// xft_xid_load_point never reads past cap, so the last sequence of the
// file needs no padding and a truncated one just fails to decode

// codepoint at f.mem[at], 0 if invalid or cut off by the end of the file
__attribute__((__always_inline__))
static inline t_u32	decode_at(t_buffer f, t_size at)
{
	return (xft_xid_decode(xft_xid_load_point(f.mem + at, f.size - at)));
}

static void	report_invalid(t_writer *w, t_buffer f, t_size at)
{
	static const char	fmt[] = "%q\tinvalid byte 0x%X\n";
	t_u64				values[2];

	values[0] = at;
	values[1] = f.mem[at];
	xft_fmt_writer(w, xft_fatptr((t_u8 *)fmt, sizeof(fmt) - 1), values);
}

// a word is a run of XID_Continue codepoints; it is an identifier if its
// first codepoint is also XID_Start, so "1x" is skipped whole instead of
// yielding "x". decode succeeded on every codepoint of the run, so the
// lead byte length is exactly how far to advance
static t_size	scan_word(t_writer *w, t_buffer f, t_size at)
{
	static const char	fmt[] = "%q\t%q\t%q\t%s\n";
	t_u64				values[5];
	t_size				end;

	values[1] = 0;
	end = at;
	while (end < f.size && xft_xid_is_continue(decode_at(f, end)))
	{
		end += xft_xid_codepoint_len(f.mem[end]);
		values[1]++;
	}
	if (!xft_xid_is_start(decode_at(f, at)))
		return (end);
	values[0] = at;
	values[2] = end - at;
	values[3] = (t_uptr)(f.mem + at);
	values[4] = end - at;
	xft_fmt_writer(w, xft_fatptr((t_u8 *)fmt, sizeof(fmt) - 1), values);
	return (end);
}

// 0 is both U+0000 and the decode error, the lead byte tells them apart.
// an invalid sequence is skipped one byte at a time, so a stray
// continuation byte after it is reported on its own
static void	scan(t_writer *w, t_buffer f)
{
	t_size	at;
	t_u32	cp;

	at = 0;
	while (at < f.size)
	{
		cp = decode_at(f, at);
		if (cp == 0 && f.mem[at] != 0)
			report_invalid(w, f, at++);
		else if (xft_xid_is_continue(cp))
			at = scan_word(w, f, at);
		else
			at += xft_xid_codepoint_len(f.mem[at]);
	}
}

__attribute__((__nonnull__(1)))
void	xft_main(const t_any *__restrict__ const sp)
{
	t_kernel_ptrs	kp;
	t_buffer		f;
	t_writer		w;
	t_u8			x[BUFSIZE];

	kp = xft_get_kernel_ptrs(sp);
	if (__builtin_expect(kp.argc != 2, 0))
		xft_exit_process(1);
	if ((t_any)kp.argv == nullptr || kp.argv[1] == nullptr)
		__builtin_unreachable();
	f = xft_map_file((const t_u8 *)kp.argv[1], xft_o_rdonly);
	xft_kernel_ptrs_destroy(&kp);
	if (f.mem == nullptr)
		xft_exit_process(1);
	w = xft_get_fs_writer(xft_fatptr(x, BUFSIZE), xft_get_stdout());
	scan(&w, f);
	(void)xft_writer_flush(&w);
	xft_unmap_file(f);
	xft_exit_process(0);
}
