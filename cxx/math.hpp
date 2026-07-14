/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
# define MATH_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace math
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: every function keeps its C name, parameter
 * order and return value, just namespaced and marked FT_NOEXCEPT (none of
 * these can throw, they are all pure __attribute__((const)) functions
 * in C; FT_NOEXCEPT is the C++98 spelling of "never unwinds"). math.h has
 * no struct with lifetime or an allocator to wrap: every type here
 * (t_fp, t_dp, t_3dcoords, ...) is a plain value type, so there is no
 * class to attach these to, exactly like hash.h. The ft_3d* functions
 * below keep their ft_ prefix (unlike every other function in this
 * codebase): stripping it would leave an identifier starting with a
 * digit ("3dsub"), which C++ does not allow. t_3dcoords/t_3dcoordsx8/
 * t_8packd/t_4packd are module-owned, not primitives, so they live under
 * c:: like every other math.h struct; a few of them are also parameter
 * names below (c), shadowing the alias, so those calls reach it through
 * its full xft::c:: spelling instead. */

inline t_f32	q_sqrt(t_f32 x) FT_NOEXCEPT
{
	return (c::ft_q_sqrt(x));
}

inline t_f64	q_dsqrt(t_f64 number) FT_NOEXCEPT
{
	return (c::ft_q_dsqrt(number));
}

inline t_f32	sqrt(t_f32 number) FT_NOEXCEPT
{
	return (c::ft_sqrt(number));
}

inline t_f64	dsqrt(t_f64 number) FT_NOEXCEPT
{
	return (c::ft_dsqrt(number));
}

inline t_f32	q_sqrt_round(t_f32 number, t_u8 n) FT_NOEXCEPT
{
	return (c::ft_q_sqrt_round(number, n));
}

inline t_f32	q_sqrt_fround(t_f32 number) FT_NOEXCEPT
{
	return (c::ft_q_sqrt_fround(number));
}

inline t_f32	roundf(t_f32 x, t_u8 n) FT_NOEXCEPT
{
	return (c::ft_roundf(x, n));
}

inline t_f32	floorf(t_f32 x) FT_NOEXCEPT
{
	return (c::ft_floorf(x));
}

inline t_f32	ceilf(t_f32 x) FT_NOEXCEPT
{
	return (c::ft_ceilf(x));
}

inline t_u128	pow_u128(t_u128 x, t_u128 n) FT_NOEXCEPT
{
	return (c::ft_pow_u128(x, n));
}

inline t_u64	pow_u64(t_u64 x, t_u64 n) FT_NOEXCEPT
{
	return (c::ft_pow_u64(x, n));
}

inline t_u32	pow_u32(t_u32 x, t_u32 n) FT_NOEXCEPT
{
	return (c::ft_pow_u32(x, n));
}

inline t_u8	pow_u8(t_u8 x, t_u8 n) FT_NOEXCEPT
{
	return (c::ft_pow_u8(x, n));
}

inline int	ipow(int x, t_u64 n) FT_NOEXCEPT
{
	return (c::ft_ipow(x, n));
}

inline long long	lpow(long long x, t_u64 n) FT_NOEXCEPT
{
	return (c::ft_lpow(x, n));
}

inline t_f32	fpow(t_f32 x, t_u64 n) FT_NOEXCEPT
{
	return (c::ft_fpow(x, n));
}

inline t_f64	dpow(t_f64 x, t_u64 n) FT_NOEXCEPT
{
	return (c::ft_dpow(x, n));
}

inline t_f32	roundff(t_f32 x) FT_NOEXCEPT
{
	return (c::ft_roundff(x));
}

inline t_f64	fabs(t_f64 x) FT_NOEXCEPT
{
	return (c::ft_fabs(x));
}

inline t_f32	rsqrt(t_f32 number) FT_NOEXCEPT
{
	return (c::ft_rsqrt(number));
}

inline t_f64	drsqrt(t_f64 number) FT_NOEXCEPT
{
	return (c::ft_drsqrt(number));
}

inline c::t_8packd	drsqrt_x8(c::t_8packd d1) FT_NOEXCEPT
{
	return (c::ft_drsqrt_x8(d1));
}

inline c::t_4packd	drsqrt_x4(c::t_4packd d1) FT_NOEXCEPT
{
	return (c::ft_drsqrt_x4(d1));
}

inline c::t_8packd	dsqrt_x8(c::t_8packd d1) FT_NOEXCEPT
{
	return (c::ft_dsqrt_x8(d1));
}

inline c::t_3dcoords	ft_3dsub(c::t_3dcoords a, c::t_3dcoords b) FT_NOEXCEPT
{
	return (c::ft_3dsub(a, b));
}

inline c::t_3dcoords	ft_3dadd(c::t_3dcoords a, c::t_3dcoords b) FT_NOEXCEPT
{
	return (c::ft_3dadd(a, b));
}

inline t_f64	ft_3dnorm(c::t_3dcoords c) FT_NOEXCEPT
{
	return (xft::c::ft_3dnorm(c));
}

inline t_f64	ft_3ddot(c::t_3dcoords a, c::t_3dcoords b) FT_NOEXCEPT
{
	return (c::ft_3ddot(a, b));
}

inline c::t_3dcoords	ft_3dunit(c::t_3dcoords c) FT_NOEXCEPT
{
	return (xft::c::ft_3dunit(c));
}

inline c::t_3dcoords	ft_3dmul(c::t_3dcoords a, c::t_3dcoords b) FT_NOEXCEPT
{
	return (c::ft_3dmul(a, b));
}

inline c::t_3dcoords	ft_3ddiv(c::t_3dcoords a, c::t_3dcoords b) FT_NOEXCEPT
{
	return (c::ft_3ddiv(a, b));
}

inline c::t_3dcoords	ft_3dcross(c::t_3dcoords a, c::t_3dcoords b) FT_NOEXCEPT
{
	return (c::ft_3dcross(a, b));
}

inline c::t_3dcoordsx8	ft_3dadd8(c::t_3dcoordsx8 a,
		c::t_3dcoordsx8 b) FT_NOEXCEPT
{
	return (c::ft_3dadd8(a, b));
}

inline c::t_3dcoordsx8	ft_3dsub8(c::t_3dcoordsx8 a,
		c::t_3dcoordsx8 b) FT_NOEXCEPT
{
	return (c::ft_3dsub8(a, b));
}

inline c::t_3dcoordsx8	ft_3dmul8(c::t_3dcoordsx8 a,
		c::t_3dcoordsx8 b) FT_NOEXCEPT
{
	return (c::ft_3dmul8(a, b));
}

inline c::t_3dcoordsx8	ft_3ddiv8(c::t_3dcoordsx8 a,
		c::t_3dcoordsx8 b) FT_NOEXCEPT
{
	return (c::ft_3ddiv8(a, b));
}

inline c::t_3dcoordsx8	ft_3dunit8(c::t_3dcoordsx8 c) FT_NOEXCEPT
{
	return (xft::c::ft_3dunit8(c));
}

inline c::t_8packd	ft_3dclampsum8(c::t_3dcoordsx8 c) FT_NOEXCEPT
{
	return (xft::c::ft_3dclampsum8(c));
}

inline c::t_8packd	ft_3dnorm8(c::t_3dcoordsx8 c) FT_NOEXCEPT
{
	return (xft::c::ft_3dnorm8(c));
}

inline c::t_8packd	ft_3ddot8(c::t_3dcoordsx8 a, c::t_3dcoordsx8 b) FT_NOEXCEPT
{
	return (c::ft_3ddot8(a, b));
}

}
}

#endif
