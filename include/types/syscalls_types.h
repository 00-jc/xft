/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALLS_TYPES_H
# define SYSCALLS_TYPES_H

# ifdef FT_REQUIRES_LIBC

#  include <fcntl.h>

typedef t_flock	t_flock;

# endif

#endif
