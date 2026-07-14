/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF_HPP
# define ELF_HPP

# include "c.hpp"

namespace xft
{
namespace elf
{

/* elf.h only defines the AT_* auxv-entry-type preprocessor macros (it
 * has no functions or structs of its own to wrap), so there is no class
 * or free function to attach here. These are exposed as namespaced
 * constants instead, so callers can write xft::elf::at_phdr the same
 * way they write xft::mem::memcpy, rather than reaching for the bare
 * un-namespaced macro. static const here gives each translation unit
 * its own copy with internal linkage, the standard C++98 way to define
 * header-only constants (matching macros.hpp's treatment). */

static const int	at_null = AT_NULL;
static const int	at_ignore = AT_IGNORE;
static const int	at_execfd = AT_EXECFD;
static const int	at_phdr = AT_PHDR;
static const int	at_phent = AT_PHENT;
static const int	at_phnum = AT_PHNUM;
static const int	at_pagesz = AT_PAGESZ;
static const int	at_base = AT_BASE;
static const int	at_flags = AT_FLAGS;
static const int	at_entry = AT_ENTRY;
static const int	at_notelf = AT_NOTELF;
static const int	at_uid = AT_UID;
static const int	at_euid = AT_EUID;
static const int	at_gid = AT_GID;
static const int	at_egid = AT_EGID;
static const int	at_platform = AT_PLATFORM;
static const int	at_hwcap = AT_HWCAP;
static const int	at_clktck = AT_CLKTCK;
static const int	at_secure = AT_SECURE;
static const int	at_base_platform = AT_BASE_PLATFORM;
static const int	at_random = AT_RANDOM;
static const int	at_hwcap2 = AT_HWCAP2;
static const int	at_execfn = AT_EXECFN;
static const int	at_sysinfo = AT_SYSINFO;
static const int	at_sysinfo_ehdr = AT_SYSINFO_EHDR;

}
}

#endif
