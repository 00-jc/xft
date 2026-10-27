/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   swissmap_types.h                                   :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWISSMAP_TYPES_H
# define SWISSMAP_TYPES_H

# include <xft/soa.h>

# ifndef SWISS_INITIAL_SIZE
#  define SWISS_INITIAL_SIZE	512
# endif

typedef struct s_swissmap
{
	t_soa		soa;
	t_size		count;
	t_size		tombstones;
}	t_swissmap;

#endif
