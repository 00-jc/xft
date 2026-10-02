/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_hash.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_HASH_H
# define XFT_P_HASH_H

# include "mem.h"
# include "hash.h"

# define MURMUR_C1	0x87c37b91114253d5ULL
# define MURMUR_C2	0x4cf5ad432745937fULL

t_u64a	rotl(t_u64a x, t_size r)\
			__attribute__((const));

t_u64a	fmix64(t_u64a k)\
			__attribute__((const));

t_u64a	xft_murmur3_tail_word(const t_u8 *restrict const tail,\
			t_size len, t_size base, t_size n)\
			__attribute__((__nonnull__(1), __pure__));

void	xft_murmur3_tail(const t_u8 *restrict const tail,\
			t_u64a k[2], t_u64a s[2], t_size len)\
			__attribute__((__nonnull__(1, 2, 3)));

#endif
