/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_hint.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:58:31 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/03 18:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_HINT_H
# define FT_P_HINT_H

# include "hint.h"

void	ft_hardcrash(void)\
			__attribute__((__noreturn__, __cold__, __noinline__));
void	ft_hardcrash_with_message(char *msg)\
			__attribute__((__noreturn__, __cold__, __noinline__,\
			__nonnull__(1)));

#endif
