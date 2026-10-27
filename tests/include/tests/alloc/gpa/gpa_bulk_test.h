/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bulk_test.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GPA_BULK_TEST_H
# define GPA_BULK_TEST_H

# include <xft/test.h>

typedef enum e_bulk_test : t_u16
{
	BULK_N = 512,
	BULK_SIZES = 4,
}	t_bulk_test;

void	test_bulk_same_size(void);
void	test_bulk_same_size_fill(t_gpa *gpa, t_buffer *bufs);
void	test_bulk_mixed_sizes(void);
void	test_bulk_mixed_sizes_fill(t_gpa *gpa, t_buffer *bufs);
void	test_bulk_reuse(void);
void	test_bulk_align(void);
void	test_gpa_bulk(t_test *t);

#endif
