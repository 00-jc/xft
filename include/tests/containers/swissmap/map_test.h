/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TEST_H
# define MAP_TEST_H

# include "private/test.h"

void	test_map_insert_lookup(t_allocator a);
void	test_map_delete(t_allocator a);
void	test_map_overwrite(t_allocator a);
void	test_map_many(t_allocator a);
void	test_map(t_test *t);

#endif
