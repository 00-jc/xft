/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include <xft/primitives.h>
# include <xft/types/sort_types.h>

void	xft_qsort(t_u8 *arr, t_qsort_ctx *c, t_size l, t_size h)\
			__attribute__((__nonnull__(1, 2)));

int		xft_cmp_u64(t_cany a, t_cany b)\
			__attribute__((__nonnull__(1, 2)));

#endif
