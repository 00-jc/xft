/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_TYPES_H
# define SORT_TYPES_H

# include <xft/primitives.h>
# include <xft/mem.h>

typedef struct s_qsort_ctx
{
	t_u8		*buf;
	t_size		size;
	t_i32		(*cmp)(t_cany, t_cany)\
				__attribute__((__nonnull__));
}	t_qsort_ctx;

#endif
