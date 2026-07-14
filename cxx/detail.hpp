/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detail.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DETAIL_HPP
# define DETAIL_HPP

/* every function in cxx/ is annotated as never-unwinding, since they
 * all report failure through explicit return values instead of C++
 * exceptions. The spelling of "never unwinds" changed between standard
 * versions: throw() (a dynamic exception-specification) is the only
 * form C++98/03 has, and it was deprecated (then removed) starting with
 * C++11 in favor of noexcept. FT_NOEXCEPT expands to whichever spelling
 * the including translation unit's standard actually supports, so the
 * same headers compile cleanly as far back as C++98 and as modern as
 * the latest standard without warnings either way. */

# if defined(__cplusplus) && __cplusplus >= 201103L
#  define FT_NOEXCEPT	noexcept
# else
#  define FT_NOEXCEPT	throw()
# endif

/* a few C functions are named after C++ reserved words (new, delete,
 * goto); the wrappers rename them (create, erase, goto_) rather than
 * overloading operator new/delete. This is not just a keyword dodge:
 * operator new/delete tie construction/destruction to a single implicit
 * allocation mechanism (::operator new forwarding to malloc, throwing
 * bad_alloc on failure), whereas every allocating call here takes an
 * explicit allocator argument (arena, gpa, page, ...) chosen per call
 * site, and this library is freestanding by default with no exceptions
 * and no guaranteed malloc underneath. create()/erase() are ordinary
 * functions that construct/tear down the wrapped C struct through
 * whichever allocator you hand them; they never allocate the wrapper
 * object's own storage the way a `new` expression would. */

#endif
