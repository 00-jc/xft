/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "primitives.h"

t_u128a		xft_murmur3(const t_u8 *__restrict__ mem, t_size size)\
				__attribute__((__nonnull__(1), pure));

t_u128a		xft_murmur3_with_seed(const t_u8 *__restrict__ mem, t_size seed,
				t_size size) __attribute__((__nonnull__(1), pure));

t_u64a		xft_xxh3_64bits(t_buffer input, t_u64a seed);

#endif
