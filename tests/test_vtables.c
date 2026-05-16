/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vtables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"
#include "alloc.h"

static void	test_palloc_vtable(void);
static void	test_arena_vtable(void);
static void	test_gpa_vtable(void);
static void	test_gpa_freelist(void);

static void	test_palloc_vtable(void)
{
	t_allocator	alloc;
	t_buffer	buf;
	t_buffer	rbuf;

	alloc = ft_new_page_alloc();
	buf = alloc.interface.allocate(alloc.allocator, 64, 8);
	ft_pin_invariant_msg(buf.mem != nullptr, (char *)"palloc: alloc non-null");
	ft_pin_invariant_msg(buf.size >= 64, (char *)"palloc: alloc size");
	buf.mem[0] = 0xAB;
	buf.mem[63] = 0xCD;
	ft_pin_invariant_msg(buf.mem[0] == 0xAB, (char *)"palloc: rw lo");
	ft_pin_invariant_msg(buf.mem[63] == 0xCD, (char *)"palloc: rw hi");
	rbuf = alloc.interface.realloc(alloc.allocator, buf, 4096, 8);
	ft_pin_invariant_msg(rbuf.mem != nullptr, (char *)"palloc: realloc ok");
	ft_pin_invariant_msg(rbuf.size >= 4096, (char *)"palloc: realloc size");
	ft_pin_invariant_msg(rbuf.mem[0] == 0xAB, (char *)"palloc: rdata lo");
	ft_pin_invariant_msg(rbuf.mem[63] == 0xCD, (char *)"palloc: rdata hi");
	alloc.interface.free(alloc.allocator, rbuf);
}

static void	test_arena_vtable(void)
{
	t_arena		arena;
	t_allocator	alloc;
	t_buffer	buf;
	t_buffer	rbuf;

	arena = ft_new_arena_alloc();
	alloc = ft_arena_allocator(&arena);
	buf = alloc.interface.allocate(alloc.allocator, 128, 16);
	ft_pin_invariant_msg(buf.mem != nullptr, (char *)"arena: alloc non-null");
	ft_pin_invariant_msg(buf.size == 128, (char *)"arena: alloc size");
	ft_pin_invariant_msg(((t_uptr)buf.mem & 15) == 0, (char *)"arena: align");
	buf.mem[0] = 0xDE;
	buf.mem[127] = 0xAD;
	rbuf = alloc.interface.realloc(alloc.allocator, buf, 256, 16);
	ft_pin_invariant_msg(rbuf.mem != nullptr, (char *)"arena: realloc ok");
	ft_pin_invariant_msg(rbuf.size == 256, (char *)"arena: realloc size");
	ft_pin_invariant_msg(rbuf.mem[0] == 0xDE, (char *)"arena: rdata lo");
	ft_pin_invariant_msg(rbuf.mem[127] == 0xAD, (char *)"arena: rdata hi");
	alloc.interface.free(alloc.allocator, rbuf);
	rbuf = alloc.interface.allocate(alloc.allocator, 64, 8);
	ft_pin_invariant_msg(rbuf.mem != nullptr, (char *)"arena: post-free alloc");
	alloc.interface.destroy(alloc.allocator);
}

static void	test_gpa_vtable(void)
{
	t_gpa		gpa;
	t_allocator	alloc;
	t_buffer	buf;
	t_buffer	rbuf;

	gpa = ft_gpa();
	ft_pin_invariant_msg(gpa.slab != nullptr, (char *)"gpa: init");
	alloc = ft_gpa_allocator(&gpa);
	buf = alloc.interface.allocate(alloc.allocator, 64, 8);
	ft_pin_invariant_msg(buf.mem != nullptr, (char *)"gpa: alloc non-null");
	ft_pin_invariant_msg(buf.size >= 64, (char *)"gpa: alloc size");
	buf.mem[0] = 0xCA;
	buf.mem[63] = 0xFE;
	ft_pin_invariant_msg(buf.mem[0] == 0xCA, (char *)"gpa: rw lo");
	ft_pin_invariant_msg(buf.mem[63] == 0xFE, (char *)"gpa: rw hi");
	rbuf = alloc.interface.realloc(alloc.allocator, buf, 512, 8);
	ft_pin_invariant_msg(rbuf.mem != nullptr, (char *)"gpa: realloc non-null");
	ft_pin_invariant_msg(rbuf.size >= 512, (char *)"gpa: realloc size");
	ft_pin_invariant_msg(rbuf.mem[0] == 0xCA, (char *)"gpa: realloc data lo");
	ft_pin_invariant_msg(rbuf.mem[63] == 0xFE, (char *)"gpa: realloc data hi");
	alloc.interface.free(alloc.allocator, rbuf);
}

static void	test_gpa_freelist(void)
{
	t_gpa		gpa;
	t_allocator	alloc;
	t_buffer	buf;
	t_buffer	buf2;

	gpa = ft_gpa();
	alloc = ft_gpa_allocator(&gpa);
	buf = alloc.interface.allocate(alloc.allocator, 64, 8);
	ft_pin_invariant_msg(buf.mem != nullptr, (char *)"gpa: freelist init");
	alloc.interface.free(alloc.allocator, buf);
	buf2 = alloc.interface.allocate(alloc.allocator, 64, 8);
	ft_pin_invariant_msg(buf2.mem != nullptr, (char *)"gpa: alloc after free");
	ft_pin_invariant_msg(buf2.mem == buf.mem, (char *)"gpa: freelist reuse");
	alloc.interface.free(alloc.allocator, buf2);
}

int	main(void)
{
	ft_printf("Testing allocator vtables...\n");
	test_palloc_vtable();
	test_arena_vtable();
	test_gpa_vtable();
	test_gpa_freelist();
	ft_printf("  vtables: OK\n");
	return (0);
}
