/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_handle_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 18:00:49 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 23:00:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "mem.h"
#include "private/ft_p_fmt.h"
#include "math.h"

__attribute__((__nonnull__(1), __always_inline__))
inline t_size	ft_fmt_uint_back(t_u8 *buf, t_u64 n)
{
	t_size	i;
	t_u64	q;

	i = 20;
	if (n == 0)
		buf[--i] = '0';
	while (n)
	{
		q = (t_u128a)n * 0xCCCCCCCCCCCCCCCDULL >> 67;
		buf[--i] = (char)((n - ((q << 3) + (q << 1))) + '0');
		n = q;
	}
	return (i);
}

__attribute__((__nonnull__(1), __always_inline__))
inline t_size	ft_fmt_double_int(t_u8 *out, t_f64 d, bool neg)
{
	t_u8	tmp[20];
	t_size	j;
	t_size	i;

	j = ft_fmt_uint_back(tmp, (t_u64)d);
	i = 0;
	if (neg)
		out[i++] = '-';
	ft_memcpy(out + i, tmp + j, 20 - j);
	return (i + 20);
}

__attribute__((__nonnull__(1), __always_inline__))
inline t_size	ft_fmt_double_frac(t_u8 *out, t_f64 frac)
{
	t_size	i;
	t_size	k;

	out[0] = '.';
	i = 1;
	k = 6;
	while (k--)
	{
		frac *= 10.0;
		out[i++] = (char)((t_u8)frac + '0');
		frac -= (t_f64)(t_u8)frac;
	}
	return (i);
}

__attribute__((__nonnull__(1), __always_inline__))
inline t_result	ft_fmt_handle_double(t_writer *__restrict__ const writer,
	t_u64 bits)
{
	t_u8	buf[32];
	t_f64	d;
	bool	neg;
	t_size	i;

	d = (t_dp){.i = bits}.f;
	if (__builtin_expect((bits & 0x7FF0000000000000ULL)
			== 0x7FF0000000000000ULL, 0))
	{
		if (bits & 0x000FFFFFFFFFFFFFULL)
			return (ft_writer_write(writer, ft_fatptr((t_u8 *)"nan", 3)));
		return (ft_writer_write(writer, ft_fatptr((t_u8 *)"inf", 3)));
	}
	if (d >= 18446744073709551616.0)
		return (ft_writer_write(writer, ft_fatptr((t_u8 *)"ovf", 3)));
	neg = d < 0.0;
	if (neg)
		d = -d;
	i = ft_fmt_double_int(buf, d, neg);
	i += ft_fmt_double_frac(buf + i, d - (t_f64)(t_u64)d);
	return (ft_writer_write(writer, ft_fatptr(buf, i)));
}
