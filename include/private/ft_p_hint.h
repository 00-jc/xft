/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_hint.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 13:46:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_HINT_H
# define FT_P_HINT_H

# include "hint.h"

void	ft_hardcrash(void)\
			__attribute__((__noreturn__, __cold__, __noinline__));
void	ft_hardcrash_with_message(t_buffer msg)\
			__attribute__((__noreturn__, __cold__, __noinline__));

#endif
