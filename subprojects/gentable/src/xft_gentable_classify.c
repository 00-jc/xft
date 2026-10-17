/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_gentable_classify.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 01:59:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 03:15:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gentable.h"

__attribute__((__nonnull__(2), __always_inline__, __used__, __hot__))
inline t_gt_classes	gt_classify(t_nvec wide,
				t_carry *__restrict__ const carry)
{
	t_gt_classes	classes;
	t_nmask			irrelevant;

	classes.digit = xft_vrangemask(wide, '0', '9');
	classes.idents = classes.digit | xft_vrangemask(wide | 0x20, 'a', 'z')
		| xft_veqmask(wide, '_') | xft_veqmask(wide, '.');
	classes.idents &= ~classes.digit;
	classes.hash = xft_veqmask(wide, '#');
	classes.newline = xft_veqmask(wide, '\n');
	classes.semicolon = xft_veqmask(wide, ';');
	irrelevant = (classes.newline - (classes.hash
				| ((*carry >> OPEN_COMMENT) & 1))) & ~classes.newline;
	classes.digit &= ~irrelevant;
	classes.idents &= ~irrelevant;
	classes.semicolon &= ~irrelevant;
	*carry &= ~((1 << OPEN_IDENT) | (1 << OPEN_NUMERAL) | (1 << OPEN_COMMENT));
	*carry |= (((classes.idents | classes.digit) >> (sizeof(t_nvec) - 1)) & 1)
		<< OPEN_IDENT;
	*carry |= (((irrelevant | classes.hash) >> (sizeof(t_nvec) - 1)) & 1)
		<< OPEN_COMMENT;
	return (classes);
}
