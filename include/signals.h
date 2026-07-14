/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:11:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 12:57:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "types/signal_types.h"

# if defined(__x86_64__) || defined(__aarch64__)

#  define FT_BLOCK		0
#  define FT_UNBLOCK	1
#  define FT_SETMASK	2

#  define FT_SIGHUP		1
#  define FT_SIGINT		2
#  define FT_SIGQUIT	3
#  define FT_SIGILL		4
#  define FT_SIGTRAP	5
#  define FT_SIGABRT	6
#  define FT_SIGBUS		7
#  define FT_SIGFPE		8
#  define FT_SIGKILL	9
#  define FT_SIGUSR1	10
#  define FT_SIGSEGV	11
#  define FT_SIGUSR2	12
#  define FT_SIGPIPE	13
#  define FT_SIGALRM	14
#  define FT_SIGTERM	15
#  define FT_SIGSTKFLT	16
#  define FT_SIGCHLD	17
#  define FT_SIGCONT	18
#  define FT_SIGSTOP	19
#  define FT_SIGTSTP	20
#  define FT_SIGTTIN	21
#  define FT_SIGTTOU	22
#  define FT_SIGURG		23
#  define FT_SIGXCPU	24
#  define FT_SIGXFSZ	25
#  define FT_SIGVTALRM	26
#  define FT_SIGPROF	27
#  define FT_SIGWINCH	28
#  define FT_SIGIO		29
#  define FT_SIGPWR		30
#  define FT_SIGSYS		31

# else

#  include <signal.h>
#  define FT_BLOCK		SIG_BLOCK
#  define FT_UNBLOCK	SIG_UNBLOCK
#  define FT_SETMASK	SIG_SETMASK
#  define FT_SIGHUP		SIGHUP
#  define FT_SIGINT		SIGINT
#  define FT_SIGQUIT	SIGQUIT
#  define FT_SIGILL		SIGILL
#  define FT_SIGTRAP	SIGTRAP
#  define FT_SIGABRT	SIGABRT
#  define FT_SIGBUS		SIGBUS
#  define FT_SIGFPE		SIGFPE
#  define FT_SIGKILL	SIGKILL
#  define FT_SIGUSR1	SIGUSR1
#  define FT_SIGSEGV	SIGSEGV
#  define FT_SIGUSR2	SIGUSR2
#  define FT_SIGPIPE	SIGPIPE
#  define FT_SIGALRM	SIGALRM
#  define FT_SIGTERM	SIGTERM
#  define FT_SIGCHLD	SIGCHLD
#  define FT_SIGCONT	SIGCONT
#  define FT_SIGSTOP	SIGSTOP
#  define FT_SIGTSTP	SIGTSTP
#  define FT_SIGTTIN	SIGTTIN
#  define FT_SIGTTOU	SIGTTOU
#  define FT_SIGURG		SIGURG
#  define FT_SIGXCPU	SIGXCPU
#  define FT_SIGXFSZ	SIGXFSZ
#  define FT_SIGVTALRM	SIGVTALRM
#  define FT_SIGPROF	SIGPROF
#  define FT_SIGWINCH	SIGWINCH
#  define FT_SIGIO		SIGIO
#  define FT_SIGSYS		SIGSYS
#  ifdef SIGSTKFLT
#   define FT_SIGSTKFLT	SIGSTKFLT
#  endif
#  ifdef SIGPWR
#   define FT_SIGPWR	SIGPWR
#  endif
# endif

t_sigset	ft_sigfillset(void);

#endif
