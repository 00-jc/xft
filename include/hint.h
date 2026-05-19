/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hint.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:56:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/12 04:29:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HINT_H
# define HINT_H

# ifdef __cplusplus

extern "C"
{

# endif

# include "types.h"
# include <stdbool.h>

void	ft_pin_invariant(int res);
void	ft_pin_invariant_msg(int res, char *msg)\
			__attribute__((__nonnull__(2)));
void	ft_assume(bool expr);

# ifdef __cplusplus
}
# endif

#endif
