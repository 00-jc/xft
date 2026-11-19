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

#include <xft/cstr.h>

__attribute__((__nonnull__(2, 3)))
t_result	xft_cstr_to_str(t_allocator allocator, t_str *str, const char *cstr)
{
	t_size		n;
	t_result	ret;

	n = xft_strlen(cstr);
	ret = xft_new_str(allocator, str, n);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	ret = xft_str_extend(allocator, str, (t_any)cstr, n);
	if (__builtin_expect(!ret.ok, 0))
		return (xft_str_destroy(allocator, str), ret);
	return ((t_result){.ok = OK});
}
