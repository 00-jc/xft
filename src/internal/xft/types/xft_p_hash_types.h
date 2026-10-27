/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_hash_types.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_HASH_TYPES_H
# define XFT_P_HASH_TYPES_H

# include <xft/primitives.h>

typedef enum e_murmur : t_u64
{
	MURMUR_C1 = 0x87c37b91114253d5,
	MURMUR_C2 = 0x4cf5ad432745937f,
}	t_murmur;

#endif
