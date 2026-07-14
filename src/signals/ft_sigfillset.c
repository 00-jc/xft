/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigfillset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:37:54 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/08 19:12:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

__attribute__((const, __always_inline__))
inline t_sigset	ft_sigfillset(void)
{
	return ((t_sigset){~0});
}
