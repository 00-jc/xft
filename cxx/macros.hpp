/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_HPP
# define MACROS_HPP

# include "c.hpp"

namespace xft
{
namespace macros
{

/* macros.h only defines string-literal preprocessor macros (they carry
 * no C linkage or namespace of their own - #define is invisible to C++
 * namespaces regardless of where the header textually expands, so
 * routing it through c.hpp above does not itself hide ANSI_RED and
 * friends; it only avoids re-expanding the header a second time), so
 * there are no functions or structs to wrap here. These are exposed as
 * namespaced constants instead, so callers can write xft::macros::ansi_red
 * the same way they write xft::mem::memcpy, rather than reaching for the
 * bare un-namespaced macro. static const here gives each translation unit
 * its own copy with internal linkage, the standard C++98 way to define
 * header-only constants. */

static const char	*const ansi_reset = ANSI_RESET;
static const char	*const ansi_black = ANSI_BLACK;
static const char	*const ansi_red = ANSI_RED;
static const char	*const ansi_green = ANSI_GREEN;
static const char	*const ansi_yellow = ANSI_YELLOW;
static const char	*const ansi_blue = ANSI_BLUE;
static const char	*const ansi_magenta = ANSI_MAGENTA;
static const char	*const ansi_cyan = ANSI_CYAN;
static const char	*const ansi_white = ANSI_WHITE;
static const char	*const ansi_bblack = ANSI_BBLACK;
static const char	*const ansi_bred = ANSI_BRED;
static const char	*const ansi_bgreen = ANSI_BGREEN;
static const char	*const ansi_byellow = ANSI_BYELLOW;
static const char	*const ansi_bblue = ANSI_BBLUE;
static const char	*const ansi_bmagenta = ANSI_BMAGENTA;
static const char	*const ansi_bcyan = ANSI_BCYAN;
static const char	*const ansi_bwhite = ANSI_BWHITE;
static const char	*const ansi_bg_red = ANSI_BG_RED;
static const char	*const ansi_bg_green = ANSI_BG_GREEN;
static const char	*const ansi_bg_yellow = ANSI_BG_YELLOW;
static const char	*const ansi_bg_blue = ANSI_BG_BLUE;
static const char	*const ansi_bg_magenta = ANSI_BG_MAGENTA;
static const char	*const ansi_bg_cyan = ANSI_BG_CYAN;
static const char	*const ansi_bg_white = ANSI_BG_WHITE;

}
}

#endif
