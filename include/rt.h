/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 23:29:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "syscalls.h"

# if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

void	_start(void)\
			__attribute__((noreturn, force_align_arg_pointer));

void	ft_rt_entry(void **sp)\
			__attribute__((noreturn, used, __nonnull__(1)));

# endif

int		ft_main(t_size argc, t_u8 **argv, t_u8 **envp)\
			__attribute__((__nonnull__(2, 3)));

#endif
