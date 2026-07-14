/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_thread.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 21:50:27 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 20:35:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_THREAD_H
# define FT_P_THREAD_H

# include "primitives.h"
# include "rt.h"
# include "threads.h"

typedef struct s_thread_offsets
{
	t_size		guard_offset;
	t_size		stack_offset;
	t_size		tls_offset;
	t_size		instance_offset;
	t_size		total_map;
}	t_thread_offset;

t_thread_offset		ft__map_bytes(const t_xft_rt *__restrict__ const rt_info,\
						const t_size stack_size)\
						__attribute__((__nonnull__(1), pure));

t_size				ft__tls_prep(const t_xft_rt *__restrict__ const rt_info,\
						t_buffer area) __attribute__((__nonnull__(1)));

t_result			ft__thread_clone(t_thread *__restrict__ const thread,\
						t_thread_offset o, t_uptr tp,\
						t_thread_instance *__restrict__ inst)\
						__attribute__((__nonnull__(1, 4)));

# if defined(__aarch64__) || defined(__aarch64_be__) \
	|| defined(__alpha__) \
	|| defined(__arm__) || defined(__ARMEB__) \
	|| defined(__hppa__) \
	|| defined(__microblaze__) || defined(__microblazeel__) \
	|| defined(__sh__) || defined(__SHEB__) \
	|| defined(__thumb__) || defined(__THUMBEB__)

#  define TLS_VARIANT_I

typedef struct s_abi_tcb
{
	t_uptr	dtv;
	t_any	_reserved;
}	t_abi_tcb;

t_size				ft__tcb_offset(const t_xft_rt *__restrict__ const rt_info)\
						__attribute__((__nonnull__(1), pure));
t_size				ft__block_offset(const t_xft_rt *__restrict__ const rt_info)\
						__attribute__((__nonnull__(1), pure));
void				ft__write_abi_tcb(t_uptr tp);

# elif defined(__arc__) || defined(__csky__) \
	|| defined(__loongarch32__) || defined(__loongarch64__) \
	|| defined(__m68k__) \
	|| defined(__mips__) || defined(__mips64__) \
	|| defined(__or1k__) \
	|| defined(__powerpc__) || defined(__powerpc64__) \
	|| defined(__riscv)

#  define TLS_VARIANT_I_MOD

typedef struct s_abi_tcb
{
	t_uptr	dtv;
}	t_abi_tcb;

t_size				ft__tcb_offset(const t_xft_rt *__restrict__ const rt_info)\
						__attribute__((__nonnull__(1), pure));
t_size				ft__block_offset(const t_xft_rt *__restrict__ const rt_info)\
						__attribute__((__nonnull__(1), pure));
void				ft__write_abi_tcb(t_uptr tp);

# elif defined(__x86_64__) || defined(__i386__) \
	|| defined(__s390x__) \
	|| defined(__sparc__) || defined(__sparc64__) \
	|| defined(__hexagon__)

#  define TLS_VARIANT_II

typedef struct s_abi_tcb
{
	struct s_abi_tcb	*self;
}	t_abi_tcb;

t_size				ft__tcb_offset(const t_xft_rt *__restrict__ const rt_info)\
						__attribute__((__nonnull__(1), pure));
t_size				ft__block_offset(const t_xft_rt *__restrict__ const rt_info)\
						__attribute__((__nonnull__(1), pure));
void				ft__write_abi_tcb(t_abi_tcb *__restrict__ const tp);

# else
#  error "xft: undefined TLS variant for this architecture"
# endif

typedef struct s_user_desc
{
	t_u32	entry_number;
	t_u32	base_addr;
	t_u32	limit;
	t_u32	seg_32bit : 1;
	t_u32	contents : 2;
	t_u32	read_exec_only : 1;
	t_u32	limit_in_pages : 1;
	t_u32	seg_not_present : 1;
	t_u32	useable : 1;
}	t_user_desc;

t_uptr				ft__settls_arg(t_uptr tp,\
						t_user_desc *__restrict__ const ud)\
						__attribute__((__nonnull__(2)));

#endif
