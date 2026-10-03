/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "types/signal_types.h"

# if defined(__x86_64__) || defined(__aarch64__)

#  define XFT_BLOCK		0
#  define XFT_UNBLOCK	1
#  define XFT_SETMASK	2

#  define XFT_SIGHUP		1
#  define XFT_SIGINT		2
#  define XFT_SIGQUIT	3
#  define XFT_SIGILL		4
#  define XFT_SIGTRAP	5
#  define XFT_SIGABRT	6
#  define XFT_SIGBUS		7
#  define XFT_SIGFPE		8
#  define XFT_SIGKILL	9
#  define XFT_SIGUSR1	10
#  define XFT_SIGSEGV	11
#  define XFT_SIGUSR2	12
#  define XFT_SIGPIPE	13
#  define XFT_SIGALRM	14
#  define XFT_SIGTERM	15
#  define XFT_SIGSTKFLT	16
#  define XFT_SIGCHLD	17
#  define XFT_SIGCONT	18
#  define XFT_SIGSTOP	19
#  define XFT_SIGTSTP	20
#  define XFT_SIGTTIN	21
#  define XFT_SIGTTOU	22
#  define XFT_SIGURG		23
#  define XFT_SIGXCPU	24
#  define XFT_SIGXFSZ	25
#  define XFT_SIGVTALRM	26
#  define XFT_SIGPROF	27
#  define XFT_SIGWINCH	28
#  define XFT_SIGIO		29
#  define XFT_SIGPWR		30
#  define XFT_SIGSYS		31

# else

#  include <signal.h>
#  define XFT_BLOCK		SIG_BLOCK
#  define XFT_UNBLOCK	SIG_UNBLOCK
#  define XFT_SETMASK	SIG_SETMASK
#  define XFT_SIGHUP		SIGHUP
#  define XFT_SIGINT		SIGINT
#  define XFT_SIGQUIT	SIGQUIT
#  define XFT_SIGILL		SIGILL
#  define XFT_SIGTRAP	SIGTRAP
#  define XFT_SIGABRT	SIGABRT
#  define XFT_SIGBUS		SIGBUS
#  define XFT_SIGFPE		SIGFPE
#  define XFT_SIGKILL	SIGKILL
#  define XFT_SIGUSR1	SIGUSR1
#  define XFT_SIGSEGV	SIGSEGV
#  define XFT_SIGUSR2	SIGUSR2
#  define XFT_SIGPIPE	SIGPIPE
#  define XFT_SIGALRM	SIGALRM
#  define XFT_SIGTERM	SIGTERM
#  define XFT_SIGCHLD	SIGCHLD
#  define XFT_SIGCONT	SIGCONT
#  define XFT_SIGSTOP	SIGSTOP
#  define XFT_SIGTSTP	SIGTSTP
#  define XFT_SIGTTIN	SIGTTIN
#  define XFT_SIGTTOU	SIGTTOU
#  define XFT_SIGURG		SIGURG
#  define XFT_SIGXCPU	SIGXCPU
#  define XFT_SIGXFSZ	SIGXFSZ
#  define XFT_SIGVTALRM	SIGVTALRM
#  define XFT_SIGPROF	SIGPROF
#  define XFT_SIGWINCH	SIGWINCH
#  define XFT_SIGIO		SIGIO
#  define XFT_SIGSYS		SIGSYS
#  ifdef SIGSTKFLT
#   define XFT_SIGSTKFLT	SIGSTKFLT
#  endif
#  ifdef SIGPWR
#   define XFT_SIGPWR	SIGPWR
#  endif
# endif

t_sigset	xft_sigfillset(void);

#endif
