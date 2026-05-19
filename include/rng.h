/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rng.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:57:11 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/14 19:18:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RNG_H
# define RNG_H

# include "types.h"
# include "bmi.h"

typedef t_u64a		t_xoshiro[4];

void		ft_xoshiro_init(t_xoshiro xoshiro)\
				__attribute__((__nonnull__(1)));
t_u64a		ft_xoshiro256ss(t_xoshiro xoshiro)\
				__attribute__((__nonnull__(1)));

#endif
