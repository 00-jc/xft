/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_hint.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
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
