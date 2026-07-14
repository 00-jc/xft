/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMI_HPP
# define BMI_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace bmi
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: every function keeps its C name, parameter
 * order and return value, just namespaced and marked FT_NOEXCEPT (none of
 * these can throw, they are all pure __attribute__((const)) bit-twiddling
 * functions; FT_NOEXCEPT is the C++98 spelling of "never unwinds"). bmi.h
 * has no struct to wrap: every function here operates on plain integer
 * values, so there is no class to attach them to, exactly like hash.h. */

inline t_u64	hasz64(t_u64 x) FT_NOEXCEPT
{
	return (c::ft_hasz64(x));
}

inline t_u64	populate(t_u8 y) FT_NOEXCEPT
{
	return (c::ft_populate(y));
}

inline t_size	memctz_u16(t_u16 x) FT_NOEXCEPT
{
	return (c::ft_memctz_u16(x));
}

inline t_size	memctz_u32(t_u32 x) FT_NOEXCEPT
{
	return (c::ft_memctz_u32(x));
}

inline t_size	memctz_u64(t_u64 x) FT_NOEXCEPT
{
	return (c::ft_memctz_u64(x));
}

inline t_size	memctz_u128(t_u128 x) FT_NOEXCEPT
{
	return (c::ft_memctz_u128(x));
}

inline t_size	memclz_u16(t_u16 x) FT_NOEXCEPT
{
	return (c::ft_memclz_u16(x));
}

inline t_size	memclz_u32(t_u32 x) FT_NOEXCEPT
{
	return (c::ft_memclz_u32(x));
}

inline t_size	memclz_u64(t_u64 x) FT_NOEXCEPT
{
	return (c::ft_memclz_u64(x));
}

inline t_size	memclz_u128(t_u128 x) FT_NOEXCEPT
{
	return (c::ft_memclz_u128(x));
}

inline t_size	max_s(t_size x, t_size y) FT_NOEXCEPT
{
	return (c::ft_max_s(x, y));
}

inline t_u8	maxu8(t_u8 x, t_u8 y) FT_NOEXCEPT
{
	return (c::ft_maxu8(x, y));
}

inline t_u32	maxu32(t_u32 x, t_u32 y) FT_NOEXCEPT
{
	return (c::ft_maxu32(x, y));
}

inline t_u64	maxu64(t_u64 x, t_u64 y) FT_NOEXCEPT
{
	return (c::ft_maxu64(x, y));
}

inline t_u128	maxu128(t_u128 x, t_u128 y) FT_NOEXCEPT
{
	return (c::ft_maxu128(x, y));
}

inline t_u16a	bswap16(t_u16a x) FT_NOEXCEPT
{
	return (c::ft_bswap16(x));
}

inline t_u32a	bswap32(t_u32a x) FT_NOEXCEPT
{
	return (c::ft_bswap32(x));
}

inline t_u64a	bswap64(t_u64a x) FT_NOEXCEPT
{
	return (c::ft_bswap64(x));
}

inline t_u16a	to_be16(t_u16a x) FT_NOEXCEPT
{
	return (c::ft_to_be16(x));
}

inline t_u32a	to_be32(t_u32a x) FT_NOEXCEPT
{
	return (c::ft_to_be32(x));
}

inline t_u64a	to_be64(t_u64a x) FT_NOEXCEPT
{
	return (c::ft_to_be64(x));
}

inline t_size	roll_mask(t_size chunk_size, t_size n) FT_NOEXCEPT
{
	return (c::ft_roll_mask(chunk_size, n));
}

inline t_u64a	rotl64(t_u64a hash, t_size n) FT_NOEXCEPT
{
	return (c::ft_rotl64(hash, n));
}

inline t_u64a	tern(t_u64a cond, t_u64a value1, t_u64a value2) FT_NOEXCEPT
{
	return (c::ft_tern(cond, value1, value2));
}

inline t_f64	dtern(t_u64a cond, t_f64 value1, t_f64 value2) FT_NOEXCEPT
{
	return (c::ft_dtern(cond, value1, value2));
}

inline t_size	next_pow2(t_size qword) FT_NOEXCEPT
{
	return (c::ft_next_pow2(qword));
}

inline t_size	last_pow2(t_size qword) FT_NOEXCEPT
{
	return (c::ft_last_pow2(qword));
}

}
}

#endif
