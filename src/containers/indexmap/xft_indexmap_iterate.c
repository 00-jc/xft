/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_indexmap_iterate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 10:35:43 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/21 11:13:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_indexmap.h>

__attribute__((__nonnull__(1), __flatten__))
void	xft_indexmap_iterate(t_indexmap *__restrict__ const map,
	t_imap_iter_callback f)
{
	t_size							it;
	t_size							rem;
	t_nvec *__restrict__ const		meta = xft_soa_fields(&map->soa,
			xft__imap_ctx(), 0);
	t_buffer *__restrict__ const	keys = xft_soa_fields(&map->soa,
			xft__imap_ctx(), 1);
	t_blk8r const					base = (t_any)meta;

	it = 0;
	while (it < map->soa.capacity_elements)
	{
		rem = map->soa.capacity_elements - it;
		f((t_nvec * __restrict__ const)(base + it), keys + it, rem);
		it += sizeof(t_nvec);
	}
}
