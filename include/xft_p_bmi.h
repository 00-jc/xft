/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_bmi.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_BMI_H
# define XFT_P_BMI_H

# include "xft_p_asm.h"

t_u64a		xft_bitpack512(t_vu512a vec)\
				__attribute__((const));

t_u32a		xft_bitpack256(t_vu256a vec)\
				__attribute__((const));

#endif
