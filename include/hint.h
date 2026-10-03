/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hint.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HINT_H
# define HINT_H

# include "primitives.h"
# include <stdbool.h>

void	xft_pin_invariant(int res);
void	xft_pin_invariant_msg(int res, t_buffer msg);
void	xft_assume(bool expr);

#endif
