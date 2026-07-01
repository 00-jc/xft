/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streaming_test.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STREAMING_TEST_H
# define STREAMING_TEST_H

# include "private/test.h"
# include "private/ft_p_mem.h"
# include "alloc/page_alloc.h"

void	test_streaming_ft_memcpy(t_buffer buf[3], t_size dst, t_size src,
			t_size len);
void	test_streaming_ft_memset(t_buffer buf[2], t_size off, t_u8 byte,
			t_size len);
void	test_streaming_mem(t_test *t);

#endif
