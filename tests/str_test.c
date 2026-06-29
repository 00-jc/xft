/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 07:01:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_str_new(t_allocator a);
void	test_str_push_back(t_allocator a);
void	test_str_extend(t_allocator a);
void	test_str_remove(t_allocator a);

void	test_str_new(t_allocator a)
{
	t_str	s;

	s = ft_str(a, 1);
	ft_pin_invariant(s.mem != nullptr);
	ft_pin_invariant(s.size == 0);
	ft_pin_invariant(s.mem[0] == 0);
	ft_str_destroy(a, &s);
	ft_pin_invariant(s.mem == nullptr);
	ft_pin_invariant(s.size == 0);
	s = ft_str(a, 5);
	ft_pin_invariant(s.mem != nullptr);
	ft_pin_invariant(s.size == 0);
	ft_pin_invariant(s.mem[5] == 0);
	ft_str_destroy(a, &s);
}

void	test_str_push_back(t_allocator a)
{
	t_str	s;

	s = ft_str(a, 1);
	ft_pin_invariant(ft_str_push_back(a, &s, 'h'));
	ft_pin_invariant(ft_str_push_back(a, &s, 'i'));
	ft_pin_invariant(s.size == 2);
	ft_pin_invariant(s.mem[0] == 'h');
	ft_pin_invariant(s.mem[1] == 'i');
	ft_pin_invariant(s.mem[2] == 0);
	ft_str_destroy(a, &s);
}

void	test_str_extend(t_allocator a)
{
	t_str		s;
	const t_u8	*hello;

	hello = (const t_u8 *)"hello";
	s = ft_str(a, 1);
	ft_pin_invariant(ft_str_extend(a, &s, hello, 5));
	ft_pin_invariant(s.size == 5);
	ft_pin_invariant(ft_memcmp(s.mem, "hello", 6) == 0);
	ft_pin_invariant(ft_str_extend(a, &s, (const t_u8 *)" world", 6));
	ft_pin_invariant(s.size == 11);
	ft_pin_invariant(ft_memcmp(s.mem, "hello world", 11) == 0);
	ft_str_destroy(a, &s);
}

void	test_str_remove(t_allocator a)
{
	t_str		s;
	const t_u8	*src;

	src = (const t_u8 *)"abc";
	s = ft_str(a, 1);
	ft_pin_invariant(ft_str_extend(a, &s, src, 3));
	ft_pin_invariant(s.size == 3);
	ft_pin_invariant(ft_str_remove(&s, 1));
	ft_pin_invariant(s.size == 2);
	ft_pin_invariant(s.mem[0] == 'a');
	ft_pin_invariant(s.mem[1] == 'c');
	ft_pin_invariant(s.mem[2] == 0);
	ft_pin_invariant(!ft_str_remove(&s, 5));
	ft_pin_invariant(ft_str_remove(&s, 0));
	ft_pin_invariant(s.size == 1);
	ft_pin_invariant(s.mem[0] == 'c');
	ft_pin_invariant(s.mem[1] == 0);
	ft_pin_invariant(ft_str_remove(&s, 0));
	ft_pin_invariant(s.size == 0);
	ft_pin_invariant(s.mem[0] == 0);
	ft_str_destroy(a, &s);
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	t_gpa		gpa;
	t_allocator	a;

	gpa = ft_gpa();
	a = ft_gpa_allocator(&gpa);
	ft_printf("Testing t_str...\n");
	test_str_new(a);
	test_str_push_back(a);
	test_str_extend(a);
	test_str_remove(a);
	ft_gpa_destroy(&gpa);
	ft_printf("  t_str: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
