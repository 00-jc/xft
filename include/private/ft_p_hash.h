/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_hash.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/19 16:36:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_HASH_H
# define FT_P_HASH_H

# ifdef __cplusplus

extern "C"
{

# endif

# include "mem.h"
# include "hash.h"

t_u64a	rotl(t_u64a x, size_t r)\
			__attribute__((const));

t_u64a	fmix64(t_u64a k)\
			__attribute__((const));

# ifdef __cplusplus
}
# endif

#endif
