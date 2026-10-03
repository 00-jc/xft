/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_cstr_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cstr.h"

__attribute__((__nonnull__(2)))
t_str	xft_cstr_to_str(t_allocator allocator, const char *cstr)
{
	t_str	str;
	t_size	n;

	n = xft_strlen(cstr);
	str = xft_new_str(allocator, n);
	if (__builtin_expect(str.mem == nullptr, 0))
		return ((t_str){0});
	if (__builtin_expect(!xft_str_extend(allocator, &str, (t_any)cstr, n), 0))
	{
		xft_str_destroy(allocator, &str);
		return ((t_str){0});
	}
	return (str);
}
