/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_pow2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 16:42:07 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 16:43:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

__attribute__((const, __always_inline__))
inline size_t	ft_next_pow2(size_t qword)
{
	return (1ULL << (64ULL - ft_memclz_u64(qword - 1)));
}
