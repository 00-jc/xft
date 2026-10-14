/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

static void	vmanip_run_w8(void)
{
	test_vmanip_native_8_a();
	test_vmanip_native_8_b();
	test_vmanip_fault_native_8();
	test_vmanip_128_8_a();
	test_vmanip_128_8_b();
	test_vmanip_fault_128_8();
	test_vmanip_256_8_a();
	test_vmanip_256_8_b();
	test_vmanip_fault_256_8();
	test_vmanip_512_8_a();
	test_vmanip_512_8_b();
	test_vmanip_fault_512_8();
}

static void	vmanip_run_w16(void)
{
	test_vmanip_native_16_a();
	test_vmanip_native_16_b();
	test_vmanip_fault_native_16();
	test_vmanip_128_16_a();
	test_vmanip_128_16_b();
	test_vmanip_fault_128_16();
	test_vmanip_256_16_a();
	test_vmanip_256_16_b();
	test_vmanip_fault_256_16();
	test_vmanip_512_16_a();
	test_vmanip_512_16_b();
	test_vmanip_fault_512_16();
}

static void	vmanip_run_w32(void)
{
	test_vmanip_native_32_a();
	test_vmanip_native_32_b();
	test_vmanip_fault_native_32();
	test_vmanip_128_32_a();
	test_vmanip_128_32_b();
	test_vmanip_fault_128_32();
	test_vmanip_256_32_a();
	test_vmanip_256_32_b();
	test_vmanip_fault_256_32();
	test_vmanip_512_32_a();
	test_vmanip_512_32_b();
	test_vmanip_fault_512_32();
}

static void	vmanip_run_w64(void)
{
	test_vmanip_native_64_a();
	test_vmanip_native_64_b();
	test_vmanip_fault_native_64();
	test_vmanip_128_64_a();
	test_vmanip_128_64_b();
	test_vmanip_fault_128_64();
	test_vmanip_256_64_a();
	test_vmanip_256_64_b();
	test_vmanip_fault_256_64();
	test_vmanip_512_64_a();
	test_vmanip_512_64_b();
	test_vmanip_fault_512_64();
}

void	test_vmanip(void)
{
	vmanip_run_w8();
	vmanip_run_w16();
	vmanip_run_w32();
	vmanip_run_w64();
}
