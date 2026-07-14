/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_HPP
# define SORT_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace sort
{

namespace c = xft::c;

/* thin, exact-semantics wrapper: cmp_u64 keeps its C name, parameter
 * order and return value, just namespaced and marked FT_NOEXCEPT (it
 * cannot throw; FT_NOEXCEPT is the C++98 spelling of "never unwinds").
 * It is a standalone comparator meant to be handed to QsortCtx's
 * constructor as a function pointer, not a method of any object, so it
 * stays a free function here - unlike qsort below, which folds
 * directly into QsortCtx::sort(). */

inline int	cmp_u64(t_cany a, t_cany b) FT_NOEXCEPT
{
	return (c::ft_cmp_u64(a, b));
}

/* QsortCtx wraps t_qsort_ctx (buf, size, cmp) as its sole state, exactly
 * the way qsort's own context does: a comparator bundle passed by
 * pointer into qsort, not an owning container (nothing here
 * allocates or frees, there is no allocator involved anywhere). Because
 * t_qsort_ctx is itself a plain copyable struct in C, QsortCtx is left
 * copyable too. */
class QsortCtx
{
	public:

		QsortCtx(void) FT_NOEXCEPT
			: _raw(c::t_qsort_ctx())
		{
		}

		QsortCtx(t_u8 *buf, t_size size,
				int (*cmp)(t_cany, t_cany)) FT_NOEXCEPT
			: _raw(c::t_qsort_ctx())
		{
			_raw.buf = buf;
			_raw.size = size;
			_raw.cmp = cmp;
		}

		void	sort(t_u8 *arr, t_size l, t_size h) FT_NOEXCEPT
		{
			c::ft_qsort(arr, &_raw, l, h);
		}

		t_u8	*buf(void) FT_NOEXCEPT
		{
			return (_raw.buf);
		}

		const t_u8	*buf(void) const FT_NOEXCEPT
		{
			return (_raw.buf);
		}

		t_size	size(void) const FT_NOEXCEPT
		{
			return (_raw.size);
		}

		c::t_qsort_ctx	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_qsort_ctx	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		explicit QsortCtx(c::t_qsort_ctx raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_qsort_ctx	_raw;
};

}
}

#endif
