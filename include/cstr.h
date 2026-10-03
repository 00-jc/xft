/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSTR_H
# define CSTR_H

# include "str.h"

t_size			xft_strlen(const char *__restrict__ str)\
					__attribute__((__nonnull__(1)));

t_str			xft_cstr_to_str(t_allocator allocator, const char *cstr)\
					__attribute__((__nonnull__(2)));

#endif
