/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_TYPES_H
# define SIGNAL_TYPES_H

# include <xft/primitives.h>

# if defined(__linux__) && !defined(__x86_64__) && !defined(__aarch64__)
#  include <signal.h>
# endif

typedef enum e_xft_sigset_size : t_u8
{
	XFT_SIGSET_SIZE = 8,
}	t_xft_sigset_size;

# if defined(__x86_64__) || defined(__aarch64__)

typedef enum e_xft_sighow : t_u8
{
	XFT_BLOCK = 0,
	XFT_UNBLOCK = 1,
	XFT_SETMASK = 2,
}	t_xft_sighow;

typedef enum e_xft_signal : t_u8
{
	XFT_SIGHUP = 1,
	XFT_SIGINT = 2,
	XFT_SIGQUIT = 3,
	XFT_SIGILL = 4,
	XFT_SIGTRAP = 5,
	XFT_SIGABRT = 6,
	XFT_SIGIOT = XFT_SIGABRT,
	XFT_SIGBUS = 7,
	XFT_SIGFPE = 8,
	XFT_SIGKILL = 9,
	XFT_SIGUSR1 = 10,
	XFT_SIGSEGV = 11,
	XFT_SIGUSR2 = 12,
	XFT_SIGPIPE = 13,
	XFT_SIGALRM = 14,
	XFT_SIGTERM = 15,
	XFT_SIGSTKFLT = 16,
	XFT_SIGCHLD = 17,
	XFT_SIGCONT = 18,
	XFT_SIGSTOP = 19,
	XFT_SIGTSTP = 20,
	XFT_SIGTTIN = 21,
	XFT_SIGTTOU = 22,
	XFT_SIGURG = 23,
	XFT_SIGXCPU = 24,
	XFT_SIGXFSZ = 25,
	XFT_SIGVTALRM = 26,
	XFT_SIGPROF = 27,
	XFT_SIGWINCH = 28,
	XFT_SIGIO = 29,
	XFT_SIGPOLL = 29,
	XFT_SIGPWR = 30,
	XFT_SIGSYS = 31,
	XFT_SIGUNUSED = XFT_SIGSYS,
}	t_xft_signal;

# elif defined(__linux__)

typedef enum e_xft_sighow : t_u8
{
	XFT_BLOCK = SIG_BLOCK,
	XFT_UNBLOCK = SIG_UNBLOCK,
	XFT_SETMASK = SIG_SETMASK,
}	t_xft_sighow;

typedef enum e_xft_signal : t_u8
{
	XFT_SIGHUP = SIGHUP,
	XFT_SIGINT = SIGINT,
	XFT_SIGQUIT = SIGQUIT,
	XFT_SIGILL = SIGILL,
	XFT_SIGTRAP = SIGTRAP,
	XFT_SIGABRT = SIGABRT,
	XFT_SIGIOT = SIGIOT,
	XFT_SIGBUS = SIGBUS,
	XFT_SIGFPE = SIGFPE,
	XFT_SIGKILL = SIGKILL,
	XFT_SIGUSR1 = SIGUSR1,
	XFT_SIGSEGV = SIGSEGV,
	XFT_SIGUSR2 = SIGUSR2,
	XFT_SIGPIPE = SIGPIPE,
	XFT_SIGALRM = SIGALRM,
	XFT_SIGTERM = SIGTERM,
	XFT_SIGCHLD = SIGCHLD,
	XFT_SIGCONT = SIGCONT,
	XFT_SIGSTOP = SIGSTOP,
	XFT_SIGTSTP = SIGTSTP,
	XFT_SIGTTIN = SIGTTIN,
	XFT_SIGTTOU = SIGTTOU,
	XFT_SIGURG = SIGURG,
	XFT_SIGXCPU = SIGXCPU,
	XFT_SIGXFSZ = SIGXFSZ,
	XFT_SIGVTALRM = SIGVTALRM,
	XFT_SIGPROF = SIGPROF,
	XFT_SIGWINCH = SIGWINCH,
	XFT_SIGIO = SIGIO,
	XFT_SIGPOLL = SIGPOLL,
	XFT_SIGSYS = SIGSYS,
}	t_xft_signal;

#  ifdef SIGSTKFLT

typedef enum e_xft_sigstkflt : t_u8
{
	XFT_SIGSTKFLT = SIGSTKFLT,
}	t_xft_sigstkflt;

#  endif

#  ifdef SIGPWR

typedef enum e_xft_sigpwr : t_u8
{
	XFT_SIGPWR = SIGPWR,
}	t_xft_sigpwr;

#  endif

#  ifdef SIGUNUSED

typedef enum e_xft_sigunused : t_u8
{
	XFT_SIGUNUSED = SIGUNUSED,
}	t_xft_sigunused;

#  endif
# endif

#endif
