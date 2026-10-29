/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_thread_start.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_THREAD_START_H
# define XFT_P_THREAD_START_H

# include <xft/threads.h>
# include <xft/types/atomic_types.h>

typedef struct s_thread_start
{
	t_thread_func	fn;
	t_any			argument;
	t_mutex			started;
}	t_thread_start;

#endif
