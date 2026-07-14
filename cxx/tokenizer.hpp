/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_HPP
# define TOKENIZER_HPP

# include "c.hpp"
# include "detail.hpp"
namespace xft
{
namespace tokenizer
{

namespace c = xft::c;

/* Token wraps t_token (mem, len) as its sole state: a non-owning view
 * into the tokenizer's underlying buffer, exactly like the C struct it
 * mirrors. */
class Token
{
	public:

		Token(void) FT_NOEXCEPT
			: _raw(c::t_token())
		{
		}

		explicit Token(c::t_token raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		t_size	len(void) const FT_NOEXCEPT
		{
			return (_raw.len);
		}

		t_u8	*data(void) FT_NOEXCEPT
		{
			return (_raw.mem);
		}

		const t_u8	*data(void) const FT_NOEXCEPT
		{
			return (_raw.mem);
		}

		c::t_token	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_token	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		c::t_token	_raw;
};

/* Tokenizer wraps t_tokenizer (mem, max, cc) as its sole state: no
 * allocator anywhere, tokenizer_* never allocates. Every method below
 * calls its ::ft_* counterpart directly - there is no free-function
 * layer sitting in between, since each one exists only to serve this
 * class. */
class Tokenizer
{
	public:

		Tokenizer(void) FT_NOEXCEPT
			: _raw(c::t_tokenizer())
		{
		}

		static Tokenizer	over(t_any mem, t_size size) FT_NOEXCEPT
		{
			return (Tokenizer(c::ft_tokenizer_over(mem, size)));
		}

		t_size	max(void) const FT_NOEXCEPT
		{
			return (_raw.max);
		}

		t_size	cursor(void) const FT_NOEXCEPT
		{
			return (_raw.cc);
		}

		Token	eat_while(const c::t_eaterset *set) FT_NOEXCEPT
		{
			return (Token(c::ft_eat_while(&_raw, set)));
		}

		Token	eat_until(const c::t_eaterset *set) FT_NOEXCEPT
		{
			return (Token(c::ft_eat_until(&_raw, set)));
		}

		/* named goto_() rather than goto(): goto is a reserved C++
		 * keyword and cannot be used as a member function name. */
		t_u32a	goto_(t_u8 byte) FT_NOEXCEPT
		{
			return (c::ft_tokenizer_goto(&_raw, byte));
		}

		void	skip_whitespace(void) FT_NOEXCEPT
		{
			c::ft_skip_whitespace(&_raw);
		}

		t_u32a	match_next(t_u8 expected) FT_NOEXCEPT
		{
			return (c::ft_match_next(&_raw, expected));
		}

		c::t_tokenizer	&raw(void) FT_NOEXCEPT
		{
			return (_raw);
		}

		const c::t_tokenizer	&raw(void) const FT_NOEXCEPT
		{
			return (_raw);
		}

	private:

		explicit Tokenizer(c::t_tokenizer raw) FT_NOEXCEPT
			: _raw(raw)
		{
		}

		c::t_tokenizer	_raw;
};

}
}

#endif
