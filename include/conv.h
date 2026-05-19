/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:59 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONV_H
# define CONV_H

# include "types.h"
# include <unistd.h>
# include <stdlib.h>

int				ft_atoi(const char *str);
ssize_t			ft_atol(const char *str);
t_f32			ft_atof(const char *s);
t_f64			ft_atod(const char *s);
int				ft_atoi_base(char *str, char *base, int base_len);
char			*ft_itoa(int n);
char			*ft_itoa_base(int n, char *base);
char			*ft_utoa_base(size_t n, char *base);
size_t			ft_atoul(const char *str)\
					__attribute__((__nonnull__(1)));
t_f64			ft_atod_bounded(const char *s, size_t n)\
					__attribute__((__nonnull__(1)));
size_t			ft_atoul_bounded(const char *__restrict__ const str,\
					size_t n) __attribute__((__nonnull__(1)));
#endif
