/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_hint.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_HINT_H
# define XFT_P_HINT_H

# include "hint.h"

void	xft_hardcrash(void)\
			__attribute__((__noreturn__, __cold__, __noinline__));
void	xft_hardcrash_with_message(t_buffer msg)\
			__attribute__((__noreturn__, __cold__, __noinline__));

#endif
