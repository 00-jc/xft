/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xxh3_secret.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_xxh3.h"

__attribute__((__always_inline__, const))
inline t_buffer	ft_xxh3_get_secret(void)
{
	static const t_secret	secret = {
		0xBE4BA423396CFEB8, 0x1CAD21F72C81017C,
		0xDB979083E96DD4DE, 0x1F67B3B7A4A44072,
		0x78E5C0CC4EE679CB, 0x2172FFCC7DD05A82,
		0x8E2443F7744608B8, 0x4C263A81E69035E0,
		0xCB00C391BB52283C, 0xA32E531B8B65D088,
		0x4EF90DA297486471, 0xD8ACDEA946EF1938,
		0x3F349CE33F76FAA8, 0x1D4F0BC7C7BBDCF9,
		0x3159B4CD4BE0518A, 0x647378D9C97E9FC8,
		0xC3EBD33483ACC5EA, 0xEB6313FAFFA081C5,
		0x49DAF0B751DD0D17, 0x9E68D429265516D3,
		0xFCA1477D58BE162B, 0xCE31D07AD1B8F88F,
		0x280416958F3ACB45, 0x7E404BBBCAFBD7AF,
	};

	return ((t_buffer){.mem = (t_u8 *)secret,
		.size = XXH3_SECRET_DEF_SIZE});
}

__attribute__((__nonnull__(1)))
void	ft_xxh3_init_custom_secret(void *custom_secret, t_u64a seed)
{
	t_size			nrounds;
	t_size			i;
	t_vu64_512a		seed_lane;
	t_vu64_512a		*rrptr[2];
	t_buffer		secret;

	secret = ft_xxh3_get_secret();
	if (secret.mem == nullptr || XXH3_SECRET_DEF_SIZE & 63
		|| (t_uptr)custom_secret & 63)
		__builtin_unreachable();
	{
		nrounds = XXH3_SECRET_DEF_SIZE / sizeof(t_vu64_512a);
		seed_lane = (t_vu64_512a){seed, -seed, seed, -seed,
			seed, -seed, seed, -seed};
		rrptr[0] = (t_vu64_512 * restrict const)secret.mem;
		rrptr[1] = (t_vu64_512 * restrict const)custom_secret;
		i = 0;
		if ((t_uptr)rrptr[0] & 63 || (t_uptr)rrptr[1] & 63)
			__builtin_unreachable();
		while (i < nrounds)
		{
			rrptr[1][i] = rrptr[0][i] + seed_lane;
			++i;
		}
	}
}
