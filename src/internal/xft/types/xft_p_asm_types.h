/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_asm_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:07:33 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 19:47:40 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_ASM_TYPES_H
# define XFT_P_ASM_TYPES_H

typedef int		t_v4si __attribute__((__aligned__(1), __vector_size__(16)));
typedef int		t_v8si __attribute__((__aligned__(1), __vector_size__(32)));

#endif
