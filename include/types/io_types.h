/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/06 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_TYPES_H
# define IO_TYPES_H

# include "primitives.h"

typedef struct s_file
{
	t_u8 *__restrict__		content;
	t_u32a					fd;
	size_t					size;
}	t_file;

#endif
