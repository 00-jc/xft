/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_ctype.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 17:35:34 by jaicastr          #+#    #+#             */
/*   Updated: 2026/02/23 17:45:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_CTYPE_H
# define FT_P_CTYPE_H

# include "private/ft_p_bmi.h"

t_u16a		ft_isalpha128(t_vu128a c)\
				__attribute__((const, hot));
t_u32a		ft_isalpha256(t_vu256a c)\
				__attribute__((const, hot));
t_u64a		ft_isalpha512(t_vu512a c)\
				__attribute__((const, hot));

t_u16a		ft_isascii128(t_vu128a c)\
				__attribute__((const, hot));
t_u32a		ft_isascii256(t_vu256a c)\
				__attribute__((const, hot));
t_u64a		ft_isascii512(t_vu512a c)\
				__attribute__((const, hot));

t_u16a		ft_isdigit128(t_vu128a c)\
				__attribute__((const, hot));
t_u32a		ft_isdigit256(t_vu256a c)\
				__attribute__((const, hot));
t_u64a		ft_isdigit512(t_vu512a c)\
				__attribute__((const, hot));

t_u16a		ft_isspace128(t_vu128a c)\
				__attribute__((const, hot));
t_u32a		ft_isspace256(t_vu256a c)\
				__attribute__((const, hot));
t_u64a		ft_isspace512(t_vu512a c)\
				__attribute__((const, hot));

t_u16a		ft_isxdigit128(t_vu128a c)\
				__attribute__((const, hot));
t_u32a		ft_isxdigit256(t_vu256a c)\
				__attribute__((const, hot));
t_u64a		ft_isxdigit512(t_vu512a c)\
				__attribute__((const, hot));

t_u16a		ft_isprint128(t_vu128a c)\
				__attribute__((const, hot));
t_u32a		ft_isprint256(t_vu256a c)\
				__attribute__((const, hot));
t_u64a		ft_isprint512(t_vu512a c)\
				__attribute__((const, hot));

#endif
