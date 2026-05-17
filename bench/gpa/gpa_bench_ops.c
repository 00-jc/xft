/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bench_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "alloc_bench.h"

void	ft_gpa_bench_8(void *ptr)
{
	t_gpa		*gpa;
	size_t		n;
	size_t		bytes;
	t_buffer	b;

	gpa = ft_get_bench_gpa();
	n = ft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		b = ft_gpa_alloc(gpa, 8, 8);
		__asm__("": "+r,m"(b.mem) ::"memory");
		bytes += b.size;
		ft_gpa_free(gpa, b);
	}
	ft_tailor_add_processed_bytes(ptr, bytes);
}

void	ft_gpa_bench_64(void *ptr)
{
	t_gpa		*gpa;
	size_t		n;
	size_t		bytes;
	t_buffer	b;

	gpa = ft_get_bench_gpa();
	n = ft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		b = ft_gpa_alloc(gpa, 64, 8);
		__asm__("": "+r,m"(b.mem) ::"memory");
		bytes += b.size;
		ft_gpa_free(gpa, b);
	}
	ft_tailor_add_processed_bytes(ptr, bytes);
}

void	ft_gpa_bench_512(void *ptr)
{
	t_gpa		*gpa;
	size_t		n;
	size_t		bytes;
	t_buffer	b;

	gpa = ft_get_bench_gpa();
	n = ft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		b = ft_gpa_alloc(gpa, 512, 8);
		__asm__("": "+r,m"(b.mem) ::"memory");
		bytes += b.size;
		ft_gpa_free(gpa, b);
	}
	ft_tailor_add_processed_bytes(ptr, bytes);
}

void	ft_gpa_bench_8k(void *ptr)
{
	t_gpa		*gpa;
	size_t		n;
	size_t		bytes;
	t_buffer	b;

	gpa = ft_get_bench_gpa();
	n = ft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		b = ft_gpa_alloc(gpa, 8192, 8);
		__asm__("": "+r,m"(b.mem) ::"memory");
		bytes += b.size;
		ft_gpa_free(gpa, b);
	}
	ft_tailor_add_processed_bytes(ptr, bytes);
}

void	ft_gpa_bench_varied(void *ptr)
{
	static const size_t	sizes[4] = {8, 64, 512, 4096};
	t_gpa				*gpa;
	size_t				n;
	size_t				bytes;
	t_buffer			b;

	gpa = ft_get_bench_gpa();
	n = ft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		b = ft_gpa_alloc(gpa, sizes[n & 3], 8);
		__asm__("": "+r,m"(b.mem) ::"memory");
		bytes += b.size;
		ft_gpa_free(gpa, b);
	}
	ft_tailor_add_processed_bytes(ptr, bytes);
}
