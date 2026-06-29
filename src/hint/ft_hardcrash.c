/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hardcrash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 15:27:42 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_hint.h"
#include "io.h"
#include "syscalls.h"

__attribute__((__noreturn__, __cold__, __noinline__))
void	ft_hardcrash_with_message(char *msg)
{
	ft_fprintf(STDERR_FILENO, "%s\n", msg);
	ft_exit(1);
}

__attribute__((__noreturn__, __cold__, __noinline__))
void	ft_hardcrash(void)
{
	ft_exit(1);
}
