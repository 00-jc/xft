/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_envp_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:22:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_rt.h"

__attribute__((__nonnull__(1), pure, __hot__, __always_inline__))
inline t_size	ft_get_envp_size(t_rt_arr envp)
{
	t_uptr	start;

	start = (t_uptr)envp;
	while (*envp)
		++envp;
	return (((t_uptr)envp - start) / sizeof(t_any));
}
