/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_bench.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 01:32:47 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/08 01:32:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBC_BENCH_H
# define LIBC_BENCH_H

# include "cstr_bench.h"
# include "tailor.h"

void	ft_libc_bench_memcpy(t_tailor *t);
void	ft_libc_bench_strlen(t_tailor *t);

void	ft_libc_memcpy_varied(t_any ptr);
void	ft_libc_memcpy_short_aligned(t_any ptr);
void	ft_libc_memcpy_short_unaligned(t_any ptr);
void	ft_libc_memcpy_medium_aligned(t_any ptr);
void	ft_libc_memcpy_medium_unaligned(t_any ptr);
void	ft_libc_memcpy_large_aligned(t_any ptr);
void	ft_libc_memcpy_large_unaligned(t_any ptr);

void	ft_libc_strlen_varied(t_any ptr);
void	ft_libc_strlen_short_aligned(t_any ptr);
void	ft_libc_strlen_short_unaligned(t_any ptr);
void	ft_libc_strlen_medium_aligned(t_any ptr);
void	ft_libc_strlen_medium_unaligned(t_any ptr);
void	ft_libc_strlen_large_aligned(t_any ptr);
void	ft_libc_strlen_large_unaligned(t_any ptr);

#endif
