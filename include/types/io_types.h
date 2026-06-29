/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:02:57 by username          #+#    #+#             */
/*   Updated: 2026/06/28 16:02:59 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_TYPES_H
# define IO_TYPES_H

# include "primitives.h"

typedef struct s_file
{
	t_u8 *__restrict__		content;
	t_u32a					fd;
	t_size					size;
}	t_file;

#endif
