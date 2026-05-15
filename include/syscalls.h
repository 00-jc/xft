/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 04:10:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 18:12:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALLS_H
# define SYSCALLS_H

# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <syscall.h>
# include "types.h"

typedef struct flock	t_flock;

void	*ft_mmap(size_t size, long prot_extra, long flags_extra);
void	*ft_fmap(size_t size, int fd);
void	ft_munmap(void *__restrict__ const mem, size_t size)\
			__attribute__((nonnull(1)));
t_u32a	ft_fcntl(t_u32a fd, t_u32a cmd,\
			const t_flock *__restrict__ const arg)\
			__attribute__((nonnull(3)));
t_u32a	ft_lockf(int fd);
t_u32a	ft_unlockf(int fd);
int		ft_stat(const char *__restrict__ path, struct stat *statbuf)\
			__attribute__((__nonnull__(1)));

void	*ft_mremap(size_t size, size_t new_size,\
			void *addr, long flags_extra)\
			__attribute__((__nonnull__(3)));

#endif
