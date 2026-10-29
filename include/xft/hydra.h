/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hydra.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 19:28:39 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 19:51:10 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HYDRA_H
# define HYDRA_H

# include <xft/primitives.h>

typedef enum e_hydra_head_type
{
	xft_hydra_heapbound,
	xft_hydra_stackbound,
}	t_hydra_head_type;

typedef struct s_hydra_head
{
	// TODO: t_signal (i don't have it yet)
	t_result			(*fn)(t_any);
	t_result			result;
	t_any				state;
	t_hydra_head_type	type;
	struct s_hydra_head	*next;
}	t_hydra_head;

#endif
