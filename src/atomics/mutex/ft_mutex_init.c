/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 18:16:34 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 18:17:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atomics.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_mutex_init(t_mutex *__restrict__ const mutex)
{
	*mutex = 0;
}
