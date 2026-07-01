/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bulk_test.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GPA_BULK_TEST_H
# define GPA_BULK_TEST_H

# include "private/test.h"
# include "alloc.h"

# define BULK_N		512
# define BULK_SIZES	4

void	test_bulk_same_size(void);
void	test_bulk_same_size_fill(t_gpa *gpa, t_buffer *bufs);
void	test_bulk_mixed_sizes(void);
void	test_bulk_mixed_sizes_fill(t_gpa *gpa, t_buffer *bufs);
void	test_bulk_reuse(void);
void	test_gpa_bulk(t_test *t);

#endif
