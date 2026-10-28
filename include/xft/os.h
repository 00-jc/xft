/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/28 22:10:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OS_H
# define OS_H

# include <xft/primitives.h>

t_result	xft_get_cpu_count(t_size *count)\
				__attribute__((__nonnull__(1)));

#endif
