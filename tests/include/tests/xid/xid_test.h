/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xid_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 05:40:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 05:40:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XID_TEST_H
# define XID_TEST_H

# include <xft/test.h>

void	test_xid_ascii(void);
void	test_xid_points(void);
void	test_xid_table(void);
void	test_xid_exhaustive(void);
void	test_xid(t_test *t);

#endif
