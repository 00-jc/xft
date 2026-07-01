/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "xft.h"
# include "str.h"
# include "hint.h"
# include "rt.h"
# include <string.h>

# define LONG_S "10000===0000000000000000000000000000000000000000000000000000"
# define LONG_M "0000000000000000900???????????????????????????????"
# define LONG_E "00000000nnnnnnnnnnnnnnnncccccccccccc"

typedef t_u8		t_misal_buffer[1024]	__attribute__((__aligned__(1)));
typedef t_u8		t_al4_buffer[1024]		__attribute__((__aligned__(4)));
typedef t_u8		t_al8_buffer[1024]		__attribute__((__aligned__(4)));
typedef t_u8		t_al64_buffer[1024]		__attribute__((__aligned__(64)));
typedef t_u8		t_al32_buffer[1024]		__attribute__((__aligned__(32)));

typedef struct s_test
{
	t_writer	writer;
	t_u8		buffer[BUFSIZE];
}	t_test;

void	ft_test_init(t_test *t);
void	ft_test_print(t_test *t, const char *msg);

#endif
