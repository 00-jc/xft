/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_TYPES_H
# define TEST_TYPES_H

# include <xft/xft.h>
# include <string.h>

# define LONG_S "10000===0000000000000000000000000000000000000000000000000000"
# define LONG_M "0000000000000000900???????????????????????????????"
# define LONG_E "00000000nnnnnnnnnnnnnnnncccccccccccc"

typedef t_u8		t_misal_buffer[1024]	__attribute__((__aligned__(1)));
typedef t_u8		t_al4_buffer[1024]		__attribute__((__aligned__(4)));
typedef t_u8		t_al8_buffer[1024]		__attribute__((__aligned__(4)));
typedef t_u8		t_al64_buffer[1024]		__attribute__((__aligned__(64)));
typedef t_u8		t_al32_buffer[1024]		__attribute__((__aligned__(32)));

typedef enum e_test_buf : t_u16
{
	TEST_BUFFER_SIZE = 4096,
}	t_test_buf;

typedef struct s_test
{
	t_writer_fs	writer_fs;
	t_writer	writer;
	t_u8		buffer[TEST_BUFFER_SIZE];
}	t_test;

#endif
