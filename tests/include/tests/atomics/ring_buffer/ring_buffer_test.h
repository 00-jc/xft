/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer_test.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RING_BUFFER_TEST_H
# define RING_BUFFER_TEST_H

# include <xft/test.h>
# include <xft/atomics.h>
# include <xft/alloc.h>
# include <stdatomic.h>

void	test_ring_buffer_init(void);
void	test_ring_buffer_fifo(void);
void	test_ring_buffer(t_test *t);

#endif
