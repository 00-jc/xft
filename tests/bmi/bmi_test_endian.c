/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmi_test_endian.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/bmi/bmi_test.h"

static void	test_endian_bytes(void)
{
	t_u32a	be;
	t_u32a	le;
	t_u8	*b;
	t_u8	*l;

	be = xft_to_be32(0x01020304);
	le = xft_to_le32(0x01020304);
	b = (t_u8 *)&be;
	l = (t_u8 *)&le;
	xft_pin_invariant(b[0] == 0x01 && b[3] == 0x04);
	xft_pin_invariant(l[0] == 0x04 && l[3] == 0x01);
}

void	test_endian(void)
{
	test_endian_bytes();
	xft_pin_invariant(xft_from_be16(xft_to_be16(0x0102)) == 0x0102);
	xft_pin_invariant(xft_from_be32(xft_to_be32(0x01020304)) == 0x01020304);
	xft_pin_invariant(xft_from_be64(xft_to_be64(0x0102030405060708ULL))
		== 0x0102030405060708ULL);
	xft_pin_invariant(xft_from_le16(xft_to_le16(0x0102)) == 0x0102);
	xft_pin_invariant(xft_from_le32(xft_to_le32(0x01020304)) == 0x01020304);
	xft_pin_invariant(xft_from_le64(xft_to_le64(0x0102030405060708ULL))
		== 0x0102030405060708ULL);
	xft_pin_invariant(xft_to_be16(0x0102) == xft_bswap16(xft_to_le16(0x0102)));
}
