/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_bmi.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:05:59 by jaicastr          #+#    #+#             */
/*   Updated: 2026/02/23 17:50:27 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_BMI_H
# define FT_P_BMI_H

# include "private/ft_p_asm.h"

t_u64a		ft_bitpack512(t_vu512a vec)\
				__attribute__((const));

t_u32a		ft_bitpack256(t_vu256a vec)\
				__attribute__((const));

#endif
