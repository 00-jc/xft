/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_TYPES_H
# define STR_TYPES_H

# include <xft/primitives.h>
# include <xft/alloc.h>

typedef struct s_str
{
	t_size	size;
	t_size	capacity;
	t_u8	*mem;
}	t_str;

#endif
