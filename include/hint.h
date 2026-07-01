/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hint.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 13:45:27 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HINT_H
# define HINT_H

# include "primitives.h"
# include <stdbool.h>

void	ft_pin_invariant(int res);
void	ft_pin_invariant_msg(int res, t_buffer msg);
void	ft_assume(bool expr);

#endif
