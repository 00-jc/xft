/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VMANIP_TEST_H
# define VMANIP_TEST_H

# include <xft/test.h>
# include <xft/types/xft_p_vmanip_types.h>

t_u8	*vmanip_guard(void);
t_size	vmanip_n(t_size bytes)\
					__attribute__((const));
t_u64	vmanip_full(t_size n)\
					__attribute__((const));
t_u64	vmanip_odd(t_size n)\
					__attribute__((const));
t_u64	vmanip_even(t_size n)\
					__attribute__((const));
t_u64	vmanip_range(t_size n)\
					__attribute__((const));
t_u64	vmanip_bit(t_size i, t_size n)\
					__attribute__((const));
t_u64	vmanip_lane(t_size i, t_size n)\
					__attribute__((const));
void	test_vmanip_native_8_a(void);
void	test_vmanip_native_8_b(void);
void	test_vmanip_fault_native_8(void);
void	test_vmanip_native_16_a(void);
void	test_vmanip_native_16_b(void);
void	test_vmanip_fault_native_16(void);
void	test_vmanip_native_32_a(void);
void	test_vmanip_native_32_b(void);
void	test_vmanip_fault_native_32(void);
void	test_vmanip_native_64_a(void);
void	test_vmanip_native_64_b(void);
void	test_vmanip_fault_native_64(void);
void	test_vmanip_128_8_a(void);
void	test_vmanip_128_8_b(void);
void	test_vmanip_fault_128_8(void);
void	test_vmanip_256_8_a(void);
void	test_vmanip_256_8_b(void);
void	test_vmanip_fault_256_8(void);
void	test_vmanip_512_8_a(void);
void	test_vmanip_512_8_b(void);
void	test_vmanip_fault_512_8(void);
void	test_vmanip_128_16_a(void);
void	test_vmanip_128_16_b(void);
void	test_vmanip_fault_128_16(void);
void	test_vmanip_256_16_a(void);
void	test_vmanip_256_16_b(void);
void	test_vmanip_fault_256_16(void);
void	test_vmanip_512_16_a(void);
void	test_vmanip_512_16_b(void);
void	test_vmanip_fault_512_16(void);
void	test_vmanip_128_32_a(void);
void	test_vmanip_128_32_b(void);
void	test_vmanip_fault_128_32(void);
void	test_vmanip_256_32_a(void);
void	test_vmanip_256_32_b(void);
void	test_vmanip_fault_256_32(void);
void	test_vmanip_512_32_a(void);
void	test_vmanip_512_32_b(void);
void	test_vmanip_fault_512_32(void);
void	test_vmanip_128_64_a(void);
void	test_vmanip_128_64_b(void);
void	test_vmanip_fault_128_64(void);
void	test_vmanip_256_64_a(void);
void	test_vmanip_256_64_b(void);
void	test_vmanip_fault_256_64(void);
void	test_vmanip_512_64_a(void);
void	test_vmanip_512_64_b(void);
void	test_vmanip_fault_512_64(void);
void	test_vmanip(void);

#endif
