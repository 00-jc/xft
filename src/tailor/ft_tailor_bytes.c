/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_bytes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_tailor_add_processed_bytes(void *ptr, const t_size bytes)
{
	t_tailor_arg	*arg;

	arg = (t_tailor_arg *)ptr;
	arg->bytes_processed += bytes;
}
