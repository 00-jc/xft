/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rng.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RNG_H
# define RNG_H

# include <xft/primitives.h>
# include <xft/types/rng_types.h>

void		xft_xoshiro_init(t_xoshiro xoshiro)\
				__attribute__((__nonnull__(1)));
t_u64a		xft_xoshiro256ss(t_xoshiro xoshiro)\
				__attribute__((__nonnull__(1)));

#endif
