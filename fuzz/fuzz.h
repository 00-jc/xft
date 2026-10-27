/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuzz.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUZZ_H
# define FUZZ_H

# include <xft/test.h>
# include <xft/fuzzer.h>

typedef enum e_fuzz_cap : t_u16
{
	FUZZ_KEY_SLOTS = 64,
	FUZZ_MEM_CAP = 1024,
	FUZZ_STR_CAP = 128,
	FUZZ_VEC_CAP = 128,
}	t_fuzz_cap;

#endif
