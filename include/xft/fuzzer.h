/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuzzer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUZZER_H
# define FUZZER_H

# include <xft/types/fuzzer_types.h>

t_fuzzer	xft_new_fuzzer(t_arena arena);
t_result	xft_fuzzer_add_rand(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));

t_buffer	*xft_fuzz_get_rand(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));
t_u64a		xft_fuzz_get_rand_u(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));
t_f64		xft_fuzz_get_rand_d(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));

void		xft_fuzzer_destroy(t_fuzzer *f)\
				__attribute__((__nonnull__(1)));

#endif
