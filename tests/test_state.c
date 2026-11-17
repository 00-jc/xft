/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:10 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:36:51 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/test.h>

void	xft_test_init(t_test *t)
{
	t->writer = xft_fs_writer(&t->writer_fs, xft_get_stdout(),
			xft_fatptr(t->buffer, TEST_BUFFER_SIZE));
}

void	xft_test_print(t_test *t, const char *msg)
{
	static t_u64	values;

	xft_fmt_writer(&t->writer, xft_fatptr((t_u8 *)msg, xft_strlen(msg)),
		&values);
}
