/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_bytes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:41:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/20 10:42:30 by jaicastr         ###   ########.fr       */
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
