/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 05:00:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "lft.h"
# include "str.h"
# include "hint.h"
# include <string.h>

# define LONG_S "10000===0000000000000000000000000000000000000000000000000000"
# define LONG_M "0000000000000000900???????????????????????????????"
# define LONG_E "00000000nnnnnnnnnnnnnnnncccccccccccc"

typedef t_u8		t_misal_buffer[1024]	__attribute__((__aligned__(1)));
typedef t_u8		t_al4_buffer[1024]		__attribute__((__aligned__(4)));
typedef t_u8		t_al8_buffer[1024]		__attribute__((__aligned__(4)));
typedef t_u8		t_al64_buffer[1024]		__attribute__((__aligned__(64)));
typedef t_u8		t_al32_buffer[1024]		__attribute__((__aligned__(32)));

#endif
