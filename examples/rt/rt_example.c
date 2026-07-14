/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_example.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 20:42:45 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/12 21:06:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft.h"

__attribute__((nonnull(1)))
void	ft_main(const t_any *__restrict__ const sp)
{
	__asm__("":: "m"(sp) :"memory");
	ft_exit(0);
}
