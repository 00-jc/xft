/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_getcount.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 03:18:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/19 03:23:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"

__attribute__((pure, __nonnull__(1)))
t_size	ft_tailor_getcount(const void *ptr)
{
	t_tailor_arg	*arg;

	arg = (t_tailor_arg *)ptr;
	return (arg->iters);
}
