/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxh3_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XXH3_TEST_H
# define XXH3_TEST_H

# include <xft/test.h>

typedef enum e_xxh3_vec : t_u64
{
	H_HELLO5_S0 = 0x9555E8555C62DCFD,
	H_WORLD5_S0 = 0xD6476C25083D69BE,
	H_ABC3_S0 = 0x78AF5F94892F3950,
	H_AB2_S0 = 0xA873719C24D5735C,
	H_A1_S0 = 0xE6C632B61E964E1F,
	H_NULL0_S0 = 0x2D06800538D394C2,
	H_NUL1_S0 = 0xC44BDFF4074EECDB,
	H_ABCD4_S0 = 0x6497A96F53A89890,
	H_NULL0_S42 = 12693748630217917650ULL,
	H_HELLO5_S1 = 0x74B07ED397A89E92,
	H_HELLO5_S42 = 0xBAFA072F07DB7937,
	H_HELLO5_SFF = 0x241E5D5372565724,
	H_A1_S42 = 0x4C437DD47F0716F4,
	H_8B_S0 = 0x6F45A76842A96483,
	H_16B_S0 = 0x3D3CCAC9AF14D8A8,
	H_17B_S0 = 0xCA7F3571DF47CACF,
	H_128B_S0 = 0x85C6174C7FF4C46B,
	H_240B_S0 = 0x375A384D957FE865,
	H_256B_S0 = 0x9408A4433B952D71,
	H_256B_S42 = 0xC1A55CA180B3FD0A,
	H_1024B_S0 = 0xA870F92984398D22,
	H_1024B_S42 = 0x2976C34B83200DF6,
}	t_xxh3_vec;

void	test_xxh3_basic(void);
void	test_xxh3_edge(void);
void	test_xxh3_seeds(void);
void	test_xxh3_lengths(t_u8 *seq);
void	test_xxh3_lengths_large(t_u8 *seq);
void	test_xxh3(t_test *t);

#endif
