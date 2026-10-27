/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_example.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 17:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 17:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOA_EXAMPLE_H
# define SOA_EXAMPLE_H

# include <xft/xft.h>

# define PARTICLES		16
# define FIELDS			5
# define STEPS			10

typedef struct s_particle
{
	t_u64a	id;
	t_i32a	x;
	t_i32a	y;
	t_i32a	vx;
	t_i32a	vy;
}	t_particle;

#endif
