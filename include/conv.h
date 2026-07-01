/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONV_H
# define CONV_H

# include "primitives.h"

int				ft_atoi(const char *str);
t_ssize			ft_atol(const char *str);
t_f32			ft_atof(const char *s);
t_f64			ft_atod(const char *s);
int				ft_atoi_base(char *str, char *base, int base_len);
char			*ft_itoa(int n);
char			*ft_itoa_base(int n, char *base);
char			*ft_utoa_base(t_size n, char *base);
t_size			ft_atoul(const char *str)\
					__attribute__((__nonnull__(1)));
t_f64			ft_atod_bounded(const char *s, t_size n)\
					__attribute__((__nonnull__(1)));
t_size			ft_atoul_bounded(const char *__restrict__ const str,\
					t_size n) __attribute__((__nonnull__(1)));
#endif
