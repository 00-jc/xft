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

#include "private/test.h"

void	ft_test_init(t_test *t)
{
	t->writer = ft_get_fs_writer(ft_fatptr(t->buffer, BUFSIZE),
			ft_get_stdout());
}

void	ft_test_print(t_test *t, const char *msg)
{
	static t_u64	values;

	ft_fmt_writer(&t->writer, ft_fatptr((t_u8 *)msg, ft_strlen(msg)),
		&values);
}
