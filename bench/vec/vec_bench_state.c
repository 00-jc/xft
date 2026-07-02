/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bench_state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:46:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 13:46:17 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "vec_bench.h"

t_gpa	*ft_get_bench_vec_gpa(void)
{
	static t_gpa	gpa = {0};

	if (gpa.slab == nullptr)
		gpa = ft_gpa();
	return (&gpa);
}
