/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 01:02:39 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:38:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# ifdef __cplusplus

extern "C"
{

# endif

# include "mem.h"

char			*ft_getenv(const char *__restrict__ const var)\
					__attribute__((__nonnull__(1)));

# ifdef __cplusplus
}
# endif

#endif
