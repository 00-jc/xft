/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_test_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/cstr/strlen/strlen_test.h"

void	test_strlen_long(void)
{
	char	buf[256];
	int		i;

	i = 0;
	while (i < 255)
	{
		buf[i] = 'A' + (i % 26);
		i++;
	}
	buf[255] = '\0';
	ft_pin_invariant(ft_strlen(buf) == strlen(buf));
	ft_pin_invariant(ft_strlen(buf + 1) == strlen(buf + 1));
	ft_pin_invariant(ft_strlen(buf + 10) == strlen(buf + 10));
	ft_pin_invariant(ft_strlen(buf + 63) == strlen(buf + 63));
}
