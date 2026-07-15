/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cpu_count_example.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:23:22 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 12:28:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft.h"

#define FMT "count: %q\n"

__attribute__((__nonnull__(1), used, noreturn))
void	ft_main(const t_any *__restrict__ sp)
{
	t_size		count;
	t_u8		x[1024];
	t_writer	w;

	(void)sp;
	if (__builtin_expect(ft_get_cpu_count(&count) == KO, 0))
		ft_exit(1);
	w = ft_get_fs_writer(ft_fatptr(x, 1024), ft_get_stdout());
	ft_fmt_writer(&w, ft_fatptr((t_u8 *)FMT, sizeof(FMT) - 1), &count);
	ft_writer_flush(&w);
	ft_exit(0);
}
