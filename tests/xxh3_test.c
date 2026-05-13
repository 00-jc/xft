/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxh3_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 08:00:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

#define H_HELLO5_S0    0x9555E8555C62DCFD
#define H_WORLD5_S0    0xD6476C25083D69BE
#define H_ABC3_S0      0x78AF5F94892F3950
#define H_AB2_S0       0xA873719C24D5735C
#define H_A1_S0        0xE6C632B61E964E1F
#define H_nullptr0_S0     0x2D06800538D394C2
#define H_NUL1_S0      0xC44BDFF4074EECDB
#define H_ABCD4_S0     0x6497A96F53A89890
#define H_nullptr0_S42    12693748630217917650ULL
#define H_HELLO5_S1    0x74B07ED397A89E92
#define H_HELLO5_S42   0xBAFA072F07DB7937
#define H_HELLO5_SFF   0x241E5D5372565724
#define H_A1_S42       0x4C437DD47F0716F4
#define H_8B_S0        0x6F45A76842A96483
#define H_16B_S0       0x3D3CCAC9AF14D8A8
#define H_17B_S0       0xCA7F3571DF47CACF
#define H_128B_S0      0x85C6174C7FF4C46B
#define H_240B_S0      0x375A384D957FE865
#define H_256B_S0      0x9408A4433B952D71
#define H_256B_S42     0xC1A55CA180B3FD0A
#define H_1024B_S0     0xA870F92984398D22
#define H_1024B_S42    0x2976C34B83200DF6

static void	test_xxh3_basic(void)
{
	t_al64_buffer	h;
	t_al4_buffer	w;
	t_al8_buffer	a;

	ft_memcpy(h, "hello", 6);
	ft_memcpy(w, "world", 6);
	ft_memcpy(a, "abc", 4);
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = h, .size = 5}, 0)
		== H_HELLO5_S0, (char *)"hello len5 seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = w, .size = 5}, 0)
		== H_WORLD5_S0, (char *)"world len5 seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = a, .size = 3}, 0)
		== H_ABC3_S0, (char *)"abc len3 seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = a, .size = 2}, 0)
		== H_AB2_S0, (char *)"ab len2 seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = a, .size = 1}, 0)
		== H_A1_S0, (char *)"a len1 seed0");
}

static void	test_xxh3_edge(void)
{
	t_al32_buffer	z;
	t_misal_buffer	nul;
	t_al4_buffer	abcd;

	z[0] = '\0';
	nul[0] = '\0';
	ft_memcpy(abcd, "abcd", 5);
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = nullptr, .size = 0},
			0) == H_nullptr0_S0, (char *)"nullptr len0 seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = z, .size = 0}, 0)
		== H_nullptr0_S0, (char *)"empty len0 seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = nul, .size = 1}, 0)
		== H_NUL1_S0, (char *)"nulbyte len1 seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = abcd, .size = 4},
			0) == H_ABCD4_S0, (char *)"abcd len4 seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = nullptr, .size = 0},
			42) == H_nullptr0_S42, (char *)"nullptr len0 seed42");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = z, .size = 0}, 42)
		== H_nullptr0_S42, (char *)"empty len0 seed42");
}

static void	test_xxh3_seeds(void)
{
	t_al32_buffer	h;
	t_misal_buffer	a;

	ft_memcpy(h, "hello", 6);
	a[0] = 'a';
	a[1] = '\0';
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = h, .size = 5}, 0)
		== H_HELLO5_S0, (char *)"hello seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = h, .size = 5}, 1)
		== H_HELLO5_S1, (char *)"hello seed1");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = h, .size = 5}, 42)
		== H_HELLO5_S42, (char *)"hello seed42");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = h, .size = 5},
			(t_u64) - 1) == H_HELLO5_SFF, (char *)"hello seedFF");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = a, .size = 1}, 42)
		== H_A1_S42, (char *)"a seed42");
}

__attribute__((__nonnull__(1)))
static void	test_xxh3_lengths(t_u8 *seq)
{
	t_al64_buffer	buf;
	t_u8			*x;

	x = &buf[3];
	ft_memcpy(x, "abcdefghijklmnopq", 17);
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = x, .size = 8}, 0)
		== H_8B_S0, (char *)"abcdefgh len8 seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = x, .size = 16},
			0) == H_16B_S0, (char *)"16B seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = x, .size = 17},
			0) == H_17B_S0, (char *)"17B seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq, .size = 128},
			0) == H_128B_S0, (char *)"128B seq seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq, .size = 240},
			0) == H_240B_S0, (char *)"240B seq seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq, .size = 256},
			0) == H_256B_S0, (char *)"256B seq seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq, .size = 256},
			42) == H_256B_S42, (char *)"256B seq seed42");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq,
			.size = 1024}, 0) == H_1024B_S0, (char *)"1024B seq seed0");
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq,
			.size = 1024}, 42) == H_1024B_S42, (char *)"1024B seq seed42");
}

int	main(void)
{
	int					i;
	t_misal_buffer		buf;

	i = 0;
	while (i < 1024)
	{
		buf[i] = (t_u8)(i % 256);
		i++;
	}
	ft_printf("Testing ft_xxh3_64bits...\n");
	test_xxh3_basic();
	test_xxh3_edge();
	test_xxh3_seeds();
	test_xxh3_lengths(buf);
	ft_printf("    ft_xxh3_64bits: OK\n");
	return (0);
}
