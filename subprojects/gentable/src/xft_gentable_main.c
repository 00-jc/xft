/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_gentable_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 01:59:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 02:22:33 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/gentable.h>
#include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1, 2), __always_inline__, __flatten__))
inline static bool	gt__init_state(t_gentable_state *__restrict__ const state,
				const char *__restrict__ const path)
{
	state->gpa = xft_new_gpa();
	if (__builtin_expect(state->gpa.slab == nullptr, 0))
		return (false);
	state->allocator = xft_gpa_allocator(&state->gpa);
	state->set = xft_new_vec(state->allocator, 512,
			sizeof(t_gentable_entry));
	if (__builtin_expect(state->set.buf.mem == nullptr, 0))
		return (xft_gpa_destroy(&state->gpa), false);
	state->database = xft_map_file((t_any)path, xft_o_rdonly);
	if (__builtin_expect(state->database.mem == nullptr, 0))
		return (xft_vec_destroy(state->allocator, &state->set),
			xft_gpa_destroy(&state->gpa), false);
	return (true);
}

__attribute__((__noreturn__, __nonnull__(1)))
void	xft_main(const t_any *__restrict__ const sp)
{
	const t_kernel_ptrs		kp = xft_get_kernel_ptrs(sp);
	t_gentable_state		state;
	t_result				ret;

	if (__builtin_expect(kp.argc != 2, 0))
		xft_exit(1);
	if (__builtin_expect(!gt__init_state(&state, (t_any)kp.argv[1]), 0))
		xft_exit(1);
	ret = gt_iterate(state.allocator, state.database, &state.set);
	if (__builtin_expect(ret == OK, 1))
		ret = gt_emit(state.database, &state.set, GT_XID_PATH);
	xft_vec_destroy(state.allocator, &state.set);
	xft_unmap_file(state.database);
	xft_gpa_destroy(&state.gpa);
	xft_exit((int)xft_tern(ret == KO, 1, 0));
}
