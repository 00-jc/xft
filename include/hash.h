/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/12 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "types.h"

t_u128a		ft_murmur3(const t_u8 *__restrict__ mem, size_t size)\
				__attribute__((__nonnull__(1), pure));

t_u128a		ft_murmur3_with_seed(const t_u8 *__restrict__ mem, size_t seed,
				size_t size) __attribute__((__nonnull__(1), pure));

t_u64a		ft_xxh3_64bits(t_buffer input, t_u64a seed);

#endif
