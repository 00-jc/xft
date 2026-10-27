/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imap_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAP_TEST_H
# define IMAP_TEST_H

# include <xft/test.h>

void	test_imap_insert_lookup(t_allocator a);
void	test_imap_delete(t_allocator a);
void	test_imap_overwrite(t_allocator a);
void	test_imap_many(t_allocator a);
void	test_imap_churn(t_allocator a);
void	test_imap_dense(t_allocator a);
void	test_imap_seeded(t_allocator a);
void	test_indexmap(t_test *t);

#endif
