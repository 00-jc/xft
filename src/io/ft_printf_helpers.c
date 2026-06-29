/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 23:54:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 22:30:32 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_io.h"
#include "math.h"

__attribute__((__always_inline__))
inline void	putu(int fd, t_size n)
{
	char			buffer[32];
	t_size			i;

	i = 32;
	if (n == 0)
		buffer[--i] = '0';
	while (n)
	{
		buffer[--i] = (char)((n % 10) + '0');
		n = (t_u128a)n * 0xCCCCCCCCCCCCCCCDULL >> 67;
	}
	i = (t_size)ft_write(fd, (t_u8 *)buffer + i, 32 - i);
	(void)i;
}

__attribute__((__always_inline__))
inline void	putx(int fd, t_size n, char or)
{
	char			buffer[32];
	t_size			i;
	char			h;

	i = 32;
	if (n == 0)
		buffer[--i] = '0';
	while (n)
	{
		h = (char)(n & 0x0F);
		buffer[--i] = (char)((h + '0' + ((h + 6) >> 4) * 7) | or);
		n >>= 4;
	}
	i = (t_size)ft_write(fd, (t_u8 *)buffer + i, 32 - i);
	(void)i;
}

__attribute__((__always_inline__))
inline void	putd(int fd, t_ssize n)
{
	char			buffer[32];
	t_u8			neg;
	t_size			i;

	i = 32;
	if (n == 0)
		buffer[--i] = '0';
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	while (n)
	{
		buffer[--i] = (char)((n % 10) + '0');
		n /= 10;
	}
	if (neg)
		buffer[--i] = '-';
	i = (t_size)ft_write(fd, (t_u8 *)buffer + i, 32 - i);
	(void)i;
}

__attribute__((__always_inline__))
inline void	puti(int fd, int n)
{
	char			buffer[32];
	t_u8			neg;
	t_size			i;

	i = 32;
	if (n == 0)
		buffer[--i] = '0';
	if (n == INT_MIN)
	{
		buffer[--i] = '8';
		n = -(n / 10);
	}
	neg = 0;
	if (n < 0)
		neg = 1;
	n = (neg == 1) * -n | (neg != 1) * n;
	while (n)
	{
		buffer[--i] = (char)((n % 10) + '0');
		n /= 10;
	}
	if (neg)
		buffer[--i] = '-';
	i = (t_size)ft_write(fd, (t_u8 *)buffer + i, 32 - i);
	(void)i;
}

__attribute__((__always_inline__))
inline void	pflt(int fd, t_f64 d)
{
	char									buffer[32];
	t_size									i;
	t_ssize __attribute__	((__unused__))	unused;
	long long								frac;
	int										p;

	if (d < 0)
		unused = ft_write(fd, (t_u8 *)"-", 1);
	d = ft_fabs(d);
	putu(fd, (t_size)d);
	frac = (long long)((d - (t_f64)(t_ssize)d) * 1000000 + 0.5);
	i = 32;
	p = 6;
	while (p--)
	{
		buffer[--i] = (char)((frac % 10) + '0');
		frac /= 10;
	}
	buffer[--i] = '.';
	unused = ft_write(fd, (t_u8 *)buffer + i, 32 - i);
}
