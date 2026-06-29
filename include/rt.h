/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 15:38:49 by username          #+#    #+#             */
/*   Updated: 2026/06/28 23:49:11 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "syscalls.h"

# if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

void	_start(void)\
			__attribute__((noreturn, force_align_arg_pointer));

# endif

int		ft_main(t_size argc, t_u8 **argv, t_u8 **envp)\
			__attribute__((__nonnull__(2, 3)));


#endif
