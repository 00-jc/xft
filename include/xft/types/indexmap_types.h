/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   indexmap_types.h                                   :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 21:00:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEXMAP_TYPES_H
# define INDEXMAP_TYPES_H

# include <xft/soa.h>

# ifndef INDEXMAP_INITIAL_SIZE
#  define INDEXMAP_INITIAL_SIZE	512
# endif

typedef enum e_indexmap_npos : t_u64
{
	INDEXMAP_NPOS = __SIZE_MAX__,
}	t_indexmap_npos;

typedef struct s_indexmap
{
	t_soa		soa;
	t_size		count;
	t_size		tombstones;
}	t_indexmap;

typedef struct s_imap_key
{
	t_buffer	key;
	t_u64a		seed;
}	t_imap_key;

typedef void	(*t_imap_iter_callback)(t_nvec *__restrict__ const meta,\
					t_buffer *__restrict__ const keys, t_size rem)\
					__attribute__((__nonnull__(1, 2)));

#endif
