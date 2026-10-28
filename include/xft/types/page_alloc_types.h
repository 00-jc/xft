/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_alloc_types.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAGE_ALLOC_TYPES_H
# define PAGE_ALLOC_TYPES_H

# include <stddef.h>
# include <xft/mem.h>

typedef enum e_hugepage_size : t_u64
{
	HUGEPAGE_2MB = 2097152,
	HUGEPAGE_8MB = 8388608,
	HUGEPAGE_16MB = 16777216,
	HUGEPAGE_256MB = 268435456,
	HUGEPAGE_512MB = 536870912,
	HUGEPAGE_1GB = 1073741824,
	HUGEPAGE_2GB = 2147483648,
	HUGEPAGE_16GB = 17179869184,
}	t_hugepage_size;

// largest tier a t_size can hold
# if UINTPTR_MAX > 0xFFFFFFFF

typedef enum e_hugepage_max : t_u64
{
	HUGEPAGE_MAX = HUGEPAGE_16GB,
}	t_hugepage_max;

# else

typedef enum e_hugepage_max : t_u64
{
	HUGEPAGE_MAX = HUGEPAGE_2GB,
}	t_hugepage_max;

# endif

typedef struct s_page_alloc
{
	t_u8	_pad;
}	t_page_alloc;

#endif
