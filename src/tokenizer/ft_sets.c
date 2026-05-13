/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:19:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_ctype.h"
#include "private/ft_p_tok.h"

#if !defined(__AVX2__) && !defined(__AVX512F__)

__attribute__((__always_inline__))
inline t_eaterset	get_eaterset(t_eater_select selection)
{
	static const t_eaterset	set[] = {
	[set_alpha] = {.eater128 = ft_isalpha128,
		.eater256 = nullptr, .eater512 = nullptr, .eater8 = ft_isalpha},
	[set_digit] = {.eater128 = ft_isdigit128,
		.eater256 = nullptr, .eater512 = nullptr, .eater8 = ft_isdigit},
	[set_xdigit] = {.eater128 = ft_isxdigit128,
		.eater256 = nullptr, .eater512 = nullptr, .eater8 = ft_isxdigit},
	[set_blank] = {.eater128 = ft_isspace128,
		.eater256 = nullptr, .eater512 = nullptr, .eater8 = ft_isspace},
	};

	return (set[selection]);
}

#elif !defined(__AVX512F__) && defined(__AVX2__)

__attribute__((__always_inline__))
inline t_eaterset	get_eaterset(t_eater_select selection)
{
	static const t_eaterset	set[] = {
	[set_alpha] = {
		.eater128 = ft_isalpha128, .eater256 = ft_isalpha256,
		.eater512 = nullptr, .eater8 = ft_isalpha},
	[set_digit] = {
		.eater128 = ft_isdigit128, .eater256 = ft_isdigit256,
		.eater512 = nullptr, .eater8 = ft_isdigit},
	[set_xdigit] = {
		.eater128 = ft_isxdigit128, .eater256 = ft_isxdigit256,
		.eater512 = nullptr, .eater8 = ft_isxdigit},
	[set_blank] = {
		.eater128 = ft_isspace128, .eater256 = ft_isspace256,
		.eater512 = nullptr, .eater8 = ft_isspace},
	};

	return (set[selection]);
}

#elif defined(__AVX512F__)

__attribute__((__always_inline__))
inline t_eaterset	get_eaterset(t_eater_select selection)
{
	static const t_eaterset	set[] = {
	[set_alpha] = {
		.eater128 = ft_isalpha128, .eater256 = ft_isalpha256,
		.eater512 = ft_isalpha512, .eater8 = ft_isalpha},
	[set_digit] = {
		.eater128 = ft_isdigit128, .eater256 = ft_isdigit256,
		.eater512 = ft_isdigit512, .eater8 = ft_isdigit},
	[set_xdigit] = {
		.eater128 = ft_isxdigit128, .eater256 = ft_isxdigit256,
		.eater512 = ft_isxdigit512, .eater8 = ft_isxdigit},
	[set_blank] = {
		.eater128 = ft_isspace128, .eater256 = ft_isspace256,
		.eater512 = ft_isspace512, .eater8 = ft_isspace},
	};

	return (set[selection]);
}

#endif
