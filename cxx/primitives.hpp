/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_HPP
# define PRIMITIVES_HPP

# define restrict	__restrict__
# define _Atomic

extern "C"
{
# include "../include/primitives.h"
}

# undef _Atomic
# undef restrict

/* primitives.h defines only plain typedefs and value structs (t_u8..t_f80a,
 * t_any/t_cany, t_size/t_ssize, t_buffer, t_result, t_span) - no functions
 * and no macros to wrap. These stay raw, unqualified C types everywhere in
 * this codebase (t_u8, t_buffer, t_result, ...), exactly as every other
 * header here already uses them, so there is no xft::primitives namespace
 * to open. */

#endif
