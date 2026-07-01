/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_alloc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAGE_ALLOC_H
# define PAGE_ALLOC_H

# include <stddef.h>
# include "syscalls.h"
# include "mem.h"

# define HUGEPAGE_2MB    2097152UL
# define HUGEPAGE_8MB    8388608UL
# define HUGEPAGE_16MB   16777216UL
# define HUGEPAGE_256MB  268435456UL
# define HUGEPAGE_512MB  536870912UL
# define HUGEPAGE_1GB    1073741824UL
# define HUGEPAGE_2GB    2147483648UL
# define HUGEPAGE_16GB   17179869184UL

# ifndef MAP_HUGE_2MB
#  define MAP_HUGE_2MB 0
# endif
# ifndef MAP_HUGE_8MB
#  define MAP_HUGE_8MB 0
# endif
# ifndef MAP_HUGE_16MB
#  define MAP_HUGE_16MB 0
# endif
# ifndef MAP_HUGE_256MB
#  define MAP_HUGE_256MB 0
# endif
# ifndef MAP_HUGE_512MB
#  define MAP_HUGE_512MB 0
# endif
# ifndef MAP_HUGE_1GB
#  define MAP_HUGE_1GB 0
# endif
# ifndef MAP_HUGE_2GB
#  define MAP_HUGE_2GB 0
# endif
# ifndef MAP_HUGE_16GB
#  define MAP_HUGE_16GB 0
# endif

typedef struct s_page_alloc
{
	t_u8	_pad;
}	t_page_alloc;

t_buffer	ft_palloc(t_size size);
t_buffer	ft_palloc_resize(t_buffer b, t_size new_size);
void		ft_palloc_free(t_buffer b);

#endif
