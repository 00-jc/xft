/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_get_rand_buffer.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 03:58:38 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/19 13:47:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tailor.h"

__attribute__((__nonnull__(1)))
t_buffer	ft_get_random_buffer(const void *ptr)
{
	t_tailor_arg	*arg;
	t_size			idx;

	arg = (t_tailor_arg *)ptr;
	idx = ft_xoshiro256ss(arg->xoshiro) % arg->buffers.size;
	return (((t_buffer *)arg->buffers.mem)[idx]);
}

__attribute__((__nonnull__(1)))
t_buffer	*ft_get_all_buffers(const void *ptr, t_size *n)
{
	t_tailor_arg	*arg;

	arg = (t_tailor_arg *)ptr;
	*n = arg->buffers.size;
	return ((t_buffer *)arg->buffers.mem);
}
