/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

#if defined(__GNUC__) && !defined(__clang__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wanalyzer-malloc-leak"
#endif

void	*ft_alloc_align(size_t size, size_t align)
{
	void	*tab;
	size_t	alloc_size;
	t_uptr	cc;
	void	*ac;

	if ((align == 0) || ((align & (align - 1)) != 0))
		return (nullptr);
	if (align < sizeof(void *))
		align = sizeof(void *);
	if (size > SIZE_MAX - (align - 1) - sizeof(void *))
		return (nullptr);
	alloc_size = sizeof(void *) + (align - 1) + size;
	tab = malloc(alloc_size);
	if (!tab)
		return (nullptr);
	cc = (t_uptr)tab + sizeof(void *);
	ac = (void *)((cc + (align - 1)) & ~(align - 1));
	return ((void)(((void **)ac)[-1] = tab), ac);
}

void	*ft_alloc(size_t size)
{
	void	*new_alloc;

	new_alloc = ft_alloc_align(size, DEF_ALIGN);
	if (!new_alloc)
		return (nullptr);
	return (new_alloc);
}

#if defined(__GNUC__) && !defined(__clang__)
# pragma GCC diagnostic pop
#endif
