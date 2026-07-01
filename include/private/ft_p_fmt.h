/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_fmt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:25:23 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 18:02:25 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_FMT_H
# define FT_P_FMT_H

# include "fmt.h"

t_result		ft_fmt_handle_hex(t_writer *__restrict__ const writer,\
					t_u64 value, bool is_lowercase)\
					__attribute__((__nonnull__(1)));

t_result		ft_fmt_handle_unsigned(t_writer *__restrict__ const writer,
					t_u64 value, t_u8 c)\
					__attribute__((__nonnull__(1)));

t_result		ft_fmt_handle_signed(t_writer *__restrict__ const writer,\
					t_u64 value, t_u8 c)\
					__attribute__((__nonnull__(1)));

t_result		ft_fmt_handle_slice(t_writer *__restrict__ const writer,
					t_u64 ptr, t_u64 len)\
					__attribute__((__nonnull__(1)));

t_result		ft_fmt_handle_double(t_writer *__restrict__ const writer,
					t_u64 bits)\
					__attribute__((__nonnull__(1)));

#endif
