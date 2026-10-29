/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_threads.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:03:22 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:04:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_THREADS_H
# define XFT_P_THREADS_H

# ifdef __linux__

#  include <xft/primitives.h>

typedef struct s_ts_offsets
{
	t_size			bytes;
	t_size			tls_offset;
	t_size			guard_offset;
	t_size			stack_offset;
	t_size			instance_offset;
}	t_ts_offsets;

# endif

#endif
