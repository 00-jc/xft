/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_HPP
# define HASH_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace hash
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: every function keeps its C name, parameter
 * order and return value, just namespaced and marked FT_NOEXCEPT (none of
 * these can throw, they report failure through explicit return values;
 * FT_NOEXCEPT is the C++98 spelling of "this function never unwinds").
 * hash.h has no struct to wrap: every function here is pure and
 * stateless, so there is no class to attach them to. */

inline t_u128a	murmur3(const t_u8 *mem, t_size size) FT_NOEXCEPT
{
	return (c::ft_murmur3(mem, size));
}

inline t_u128a	murmur3_with_seed(const t_u8 *mem, t_size seed,
		t_size size) FT_NOEXCEPT
{
	return (c::ft_murmur3_with_seed(mem, seed, size));
}

inline t_u64a	xxh3_64bits(t_buffer input, t_u64a seed) FT_NOEXCEPT
{
	return (c::ft_xxh3_64bits(input, seed));
}

}
}

#endif
