/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_get_random_num.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 09:54:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 09:55:01 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"

__attribute__((__nonnull__(1), __always_inline__))
inline size_t	ft_tailor_get_random_num(void *ptr)
{
	t_tailor_arg	*arg;

	arg = ptr;
	return (ft_xoshiro256ss(arg->xoshiro));
}
