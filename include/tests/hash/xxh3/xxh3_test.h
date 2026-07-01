/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxh3_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XXH3_TEST_H
# define XXH3_TEST_H

# include "private/test.h"

# define H_HELLO5_S0    0x9555E8555C62DCFD
# define H_WORLD5_S0    0xD6476C25083D69BE
# define H_ABC3_S0      0x78AF5F94892F3950
# define H_AB2_S0       0xA873719C24D5735C
# define H_A1_S0        0xE6C632B61E964E1F
# define H_NULL0_S0     0x2D06800538D394C2
# define H_NUL1_S0      0xC44BDFF4074EECDB
# define H_ABCD4_S0     0x6497A96F53A89890
# define H_NULL0_S42    12693748630217917650ULL
# define H_HELLO5_S1    0x74B07ED397A89E92
# define H_HELLO5_S42   0xBAFA072F07DB7937
# define H_HELLO5_SFF   0x241E5D5372565724
# define H_A1_S42       0x4C437DD47F0716F4
# define H_8B_S0        0x6F45A76842A96483
# define H_16B_S0       0x3D3CCAC9AF14D8A8
# define H_17B_S0       0xCA7F3571DF47CACF
# define H_128B_S0      0x85C6174C7FF4C46B
# define H_240B_S0      0x375A384D957FE865
# define H_256B_S0      0x9408A4433B952D71
# define H_256B_S42     0xC1A55CA180B3FD0A
# define H_1024B_S0     0xA870F92984398D22
# define H_1024B_S42    0x2976C34B83200DF6

void	test_xxh3_basic(void);
void	test_xxh3_edge(void);
void	test_xxh3_seeds(void);
void	test_xxh3_lengths(t_u8 *seq);
void	test_xxh3_lengths_large(t_u8 *seq);
void	test_xxh3(t_test *t);

#endif
