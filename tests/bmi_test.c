/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmi_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/08 02:43:08 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_ctz(void);
void	test_clz(void);
void	test_bswap(void);
void	test_max(void);

void	test_ctz(void)
{
	ft_pin_invariant(ft_memctz_u32(1) == 0);
	ft_pin_invariant(ft_memctz_u32(2) == 1);
	ft_pin_invariant(ft_memctz_u32(4) == 2);
	ft_pin_invariant(ft_memctz_u32(0x80) == 7);
	ft_pin_invariant(ft_memctz_u32(0x80000000U) == 31);
	ft_pin_invariant(ft_memctz_u64(1) == 0);
	ft_pin_invariant(ft_memctz_u64(0x100) == 8);
	ft_pin_invariant(ft_memctz_u64(0x8000000000000000ULL) == 63);
	ft_pin_invariant(ft_memctz_u16(1) == 0);
	ft_pin_invariant(ft_memctz_u16(0x8000) == 15);
}

void	test_clz(void)
{
	ft_pin_invariant(ft_memclz_u32(1) == 31);
	ft_pin_invariant(ft_memclz_u32(2) == 30);
	ft_pin_invariant(ft_memclz_u32(0x80000000U) == 0);
	ft_pin_invariant(ft_memclz_u32(0xFF) == 24);
	ft_pin_invariant(ft_memclz_u64(1) == 63);
	ft_pin_invariant(ft_memclz_u64(0x8000000000000000ULL) == 0);
	ft_pin_invariant(ft_memclz_u16(1) == 15);
	ft_pin_invariant(ft_memclz_u16(0x8000) == 0);
}

void	test_bswap(void)
{
	ft_pin_invariant(ft_bswap16(0x0102) == 0x0201);
	ft_pin_invariant(ft_bswap32(0x01020304) == 0x04030201);
	ft_pin_invariant(ft_bswap64(0x0102030405060708ULL)
		== 0x0807060504030201ULL);
	ft_pin_invariant(ft_bswap16(0) == 0);
	ft_pin_invariant(ft_bswap32(0) == 0);
	ft_pin_invariant(ft_bswap64(0) == 0);
}

void	test_max(void)
{
	ft_pin_invariant(ft_max_s(1, 2) == 2);
	ft_pin_invariant(ft_max_s(100, 50) == 100);
	ft_pin_invariant(ft_max_s(0, 0) == 0);
	ft_pin_invariant(ft_maxu8(10, 20) == 20);
	ft_pin_invariant(ft_maxu8(255, 0) == 255);
	ft_pin_invariant(ft_maxu32(0, 0xFFFFFFFF) == 0xFFFFFFFF);
	ft_pin_invariant(ft_maxu64(42, 42) == 42);
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	ft_printf("Testing bmi...\n");
	test_ctz();
	test_clz();
	test_bswap();
	test_max();
	ft_printf("  bmi: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
