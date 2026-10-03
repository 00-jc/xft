/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_syscalls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_SYSCALLS_H
# define XFT_P_SYSCALLS_H

# ifndef __linux__
#  error "xft_p_syscalls.h is the linux backend's: syscall numbers stay here"
# endif

# include "syscalls.h"

# ifdef XFT_REQUIRE_LIBC
#  include <sys/syscall.h>
#  include <syscall.h>
# endif

# ifndef FUTEX_WAIT
#  define FUTEX_WAIT               0
#  define FUTEX_WAKE               1
#  define FUTEX_REQUEUE            3
#  define FUTEX_CMP_REQUEUE        4
#  define FUTEX_WAKE_OP            5
#  define FUTEX_LOCK_PI            6
#  define FUTEX_UNLOCK_PI          7
#  define FUTEX_TRYLOCK_PI         8
#  define FUTEX_WAIT_BITSET        9
#  define FUTEX_WAKE_BITSET        10
#  define FUTEX_WAIT_REQUEUE_PI    11
#  define FUTEX_CMP_REQUEUE_PI     12
#  define FUTEX_LOCK_PI2           13
# endif

# ifndef CLONE_VM
#  define CLONE_VM                   0x00000100
# endif
# ifndef CLONE_FS
#  define CLONE_FS                   0x00000200
# endif
# ifndef CLONE_FILES
#  define CLONE_FILES                0x00000400
# endif
# ifndef CLONE_SIGHAND
#  define CLONE_SIGHAND              0x00000800
# endif
# ifndef CLONE_THREAD
#  define CLONE_THREAD               0x00010000
# endif
# ifndef CLONE_SYSVSEM
#  define CLONE_SYSVSEM              0x00040000
# endif
# ifndef CLONE_SETTLS
#  define CLONE_SETTLS               0x00080000
# endif
# ifndef CLONE_PARENT_SETTID
#  define CLONE_PARENT_SETTID        0x00100000
# endif
# ifndef CLONE_CHILD_CLEARTID
#  define CLONE_CHILD_CLEARTID       0x00200000
# endif
# ifndef CLONE_CHILD_SETTID
#  define CLONE_CHILD_SETTID         0x01000000
# endif

# if defined(__x86_64__) && defined(__linux__) && !defined(XFT_REQUIRE_LIBC)

#  ifndef AT_FDCWD
#   define AT_FDCWD                   -100
#  endif
#  define SYS_READ                    0
#  define SYS_WRITE                   1
#  define SYS_OPEN                    2
#  define SYS_CLOSE                   3
#  define SYS_STAT                    4
#  define SYS_FSTAT                   5
#  define SYS_LSTAT                   6
#  define SYS_POLL                    7
#  define SYS_LSEEK                   8
#  define SYS_MMAP                    9
#  define SYS_MPROTECT                10
#  define SYS_MUNMAP                  11
#  define SYS_BRK                     12
#  define SYS_RT_SIGACTION            13
#  define SYS_RT_SIGPROCMASK          14
#  define SYS_RT_SIGRETURN            15
#  define SYS_IOCTL                   16
#  define SYS_PREAD64                 17
#  define SYS_PWRITE64                18
#  define SYS_READV                   19
#  define SYS_WRITEV                  20
#  define SYS_ACCESS                  21
#  define SYS_PIPE                    22
#  define SYS_SELECT                  23
#  define SYS_SCHED_YIELD             24
#  define SYS_MREMAP                  25
#  define SYS_MSYNC                   26
#  define SYS_MINCORE                 27
#  define SYS_MADVISE                 28
#  define SYS_SHMGET                  29
#  define SYS_SHMAT                   30
#  define SYS_SHMCTL                  31
#  define SYS_DUP                     32
#  define SYS_DUP2                    33
#  define SYS_PAUSE                   34
#  define SYS_NANOSLEEP               35
#  define SYS_GETITIMER               36
#  define SYS_ALARM                   37
#  define SYS_SETITIMER               38
#  define SYS_GETPID                  39
#  define SYS_SENDFILE                40
#  define SYS_SOCKET                  41
#  define SYS_CONNECT                 42
#  define SYS_ACCEPT                  43
#  define SYS_SENDTO                  44
#  define SYS_RECVFROM                45
#  define SYS_SENDMSG                 46
#  define SYS_RECVMSG                 47
#  define SYS_SHUTDOWN                48
#  define SYS_BIND                    49
#  define SYS_LISTEN                  50
#  define SYS_GETSOCKNAME             51
#  define SYS_GETPEERNAME             52
#  define SYS_SOCKETPAIR              53
#  define SYS_SETSOCKOPT              54
#  define SYS_GETSOCKOPT              55
#  define SYS_CLONE                   56
#  define SYS_FORK                    57
#  define SYS_VFORK                   58
#  define SYS_EXECVE                  59
#  define SYS_EXIT                    60
#  define SYS_WAIT4                   61
#  define SYS_KILL                    62
#  define SYS_UNAME                   63
#  define SYS_SEMGET                  64
#  define SYS_SEMOP                   65
#  define SYS_SEMCTL                  66
#  define SYS_SHMDT                   67
#  define SYS_MSGGET                  68
#  define SYS_MSGSND                  69
#  define SYS_MSGRCV                  70
#  define SYS_MSGCTL                  71
#  define SYS_FCNTL                   72
#  define SYS_FLOCK                   73
#  define SYS_FSYNC                   74
#  define SYS_FDATASYNC               75
#  define SYS_TRUNCATE                76
#  define SYS_FTRUNCATE               77
#  define SYS_GETDENTS                78
#  define SYS_GETCWD                  79
#  define SYS_CHDIR                   80
#  define SYS_FCHDIR                  81
#  define SYS_RENAME                  82
#  define SYS_MKDIR                   83
#  define SYS_RMDIR                   84
#  define SYS_CREAT                   85
#  define SYS_LINK                    86
#  define SYS_UNLINK                  87
#  define SYS_SYMLINK                 88
#  define SYS_READLINK                89
#  define SYS_CHMOD                   90
#  define SYS_FCHMOD                  91
#  define SYS_CHOWN                   92
#  define SYS_FCHOWN                  93
#  define SYS_LCHOWN                  94
#  define SYS_UMASK                   95
#  define SYS_GETTIMEOFDAY            96
#  define SYS_GETRLIMIT               97
#  define SYS_GETRUSAGE               98
#  define SYS_SYSINFO                 99
#  define SYS_TIMES                   100
#  define SYS_PTRACE                  101
#  define SYS_GETUID                  102
#  define SYS_SYSLOG                  103
#  define SYS_GETGID                  104
#  define SYS_SETUID                  105
#  define SYS_SETGID                  106
#  define SYS_GETEUID                 107
#  define SYS_GETEGID                 108
#  define SYS_SETPGID                 109
#  define SYS_GETPPID                 110
#  define SYS_GETPGRP                 111
#  define SYS_SETSID                  112
#  define SYS_SETREUID                113
#  define SYS_SETREGID                114
#  define SYS_GETGROUPS               115
#  define SYS_SETGROUPS               116
#  define SYS_SETRESUID               117
#  define SYS_GETRESUID               118
#  define SYS_SETRESGID               119
#  define SYS_GETRESGID               120
#  define SYS_GETPGID                 121
#  define SYS_SETFSUID                122
#  define SYS_SETFSGID                123
#  define SYS_GETSID                  124
#  define SYS_CAPGET                  125
#  define SYS_CAPSET                  126
#  define SYS_RT_SIGPENDING           127
#  define SYS_RT_SIGTIMEDWAIT         128
#  define SYS_RT_SIGQUEUEINFO         129
#  define SYS_RT_SIGSUSPEND           130
#  define SYS_SIGALTSTACK             131
#  define SYS_UTIME                   132
#  define SYS_MKNOD                   133
#  define SYS_USELIB                  134
#  define SYS_PERSONALITY             135
#  define SYS_USTAT                   136
#  define SYS_STATFS                  137
#  define SYS_FSTATFS                 138
#  define SYS_SYSFS                   139
#  define SYS_GETPRIORITY             140
#  define SYS_SETPRIORITY             141
#  define SYS_SCHED_SETPARAM          142
#  define SYS_SCHED_GETPARAM          143
#  define SYS_SCHED_SETSCHEDULER      144
#  define SYS_SCHED_GETSCHEDULER      145
#  define SYS_SCHED_GET_PRIORITY_MAX  146
#  define SYS_SCHED_GET_PRIORITY_MIN  147
#  define SYS_SCHED_RR_GET_INTERVAL   148
#  define SYS_MLOCK                   149
#  define SYS_MUNLOCK                 150
#  define SYS_MLOCKALL                151
#  define SYS_MUNLOCKALL              152
#  define SYS_VHANGUP                 153
#  define SYS_MODIFY_LDT              154
#  define SYS_PIVOT_ROOT              155
#  define SYS__SYSCTL                 156
#  define SYS_PRCTL                   157
#  define SYS_ARCH_PRCTL              158
#  define SYS_ADJTIMEX                159
#  define SYS_SETRLIMIT               160
#  define SYS_CHROOT                  161
#  define SYS_SYNC                    162
#  define SYS_ACCT                    163
#  define SYS_SETTIMEOFDAY            164
#  define SYS_MOUNT                   165
#  define SYS_UMOUNT2                 166
#  define SYS_SWAPON                  167
#  define SYS_SWAPOFF                 168
#  define SYS_REBOOT                  169
#  define SYS_SETHOSTNAME             170
#  define SYS_SETDOMAINNAME           171
#  define SYS_IOPL                    172
#  define SYS_IOPERM                  173
#  define SYS_CREATE_MODULE           174
#  define SYS_INIT_MODULE             175
#  define SYS_DELETE_MODULE           176
#  define SYS_GET_KERNEL_SYMS         177
#  define SYS_QUERY_MODULE            178
#  define SYS_QUOTACTL                179
#  define SYS_NFSSERVCTL              180
#  define SYS_GETPMSG                 181
#  define SYS_PUTPMSG                 182
#  define SYS_AFS_SYSCALL             183
#  define SYS_TUXCALL                 184
#  define SYS_SECURITY                185
#  define SYS_GETTID                  186
#  define SYS_READAHEAD               187
#  define SYS_SETXATTR                188
#  define SYS_LSETXATTR               189
#  define SYS_FSETXATTR               190
#  define SYS_GETXATTR                191
#  define SYS_LGETXATTR               192
#  define SYS_FGETXATTR               193
#  define SYS_LISTXATTR               194
#  define SYS_LLISTXATTR              195
#  define SYS_FLISTXATTR              196
#  define SYS_REMOVEXATTR             197
#  define SYS_LREMOVEXATTR            198
#  define SYS_FREMOVEXATTR            199
#  define SYS_TKILL                   200
#  define SYS_TIME                    201
#  define SYS_FUTEX                   202
#  define SYS_SCHED_SETAFFINITY       203
#  define SYS_SCHED_GETAFFINITY       204
#  define SYS_SET_THREAD_AREA         205
#  define SYS_IO_SETUP                206
#  define SYS_IO_DESTROY              207
#  define SYS_IO_GETEVENTS            208
#  define SYS_IO_SUBMIT               209
#  define SYS_IO_CANCEL               210
#  define SYS_GET_THREAD_AREA         211
#  define SYS_LOOKUP_DCOOKIE          212
#  define SYS_EPOLL_CREATE            213
#  define SYS_EPOLL_CTL_OLD           214
#  define SYS_EPOLL_WAIT_OLD          215
#  define SYS_REMAP_FILE_PAGES        216
#  define SYS_GETDENTS64              217
#  define SYS_SET_TID_ADDRESS         218
#  define SYS_RESTART_SYSCALL         219
#  define SYS_SEMTIMEDOP              220
#  define SYS_FADVISE64               221
#  define SYS_TIMER_CREATE            222
#  define SYS_TIMER_SETTIME           223
#  define SYS_TIMER_GETTIME           224
#  define SYS_TIMER_GETOVERRUN        225
#  define SYS_TIMER_DELETE            226
#  define SYS_CLOCK_SETTIME           227
#  define SYS_CLOCK_GETTIME           228
#  define SYS_CLOCK_GETRES            229
#  define SYS_CLOCK_NANOSLEEP         230
#  define SYS_EXIT_GROUP              231
#  define SYS_EPOLL_WAIT              232
#  define SYS_EPOLL_CTL               233
#  define SYS_TGKILL                  234
#  define SYS_UTIMES                  235
#  define SYS_VSERVER                 236
#  define SYS_MBIND                   237
#  define SYS_SET_MEMPOLICY           238
#  define SYS_GET_MEMPOLICY           239
#  define SYS_MQ_OPEN                 240
#  define SYS_MQ_UNLINK               241
#  define SYS_MQ_TIMEDSEND            242
#  define SYS_MQ_TIMEDRECEIVE         243
#  define SYS_MQ_NOTIFY               244
#  define SYS_MQ_GETSETATTR           245
#  define SYS_KEXEC_LOAD              246
#  define SYS_WAITID                  247
#  define SYS_ADD_KEY                 248
#  define SYS_REQUEST_KEY             249
#  define SYS_KEYCTL                  250
#  define SYS_IOPRIO_SET              251
#  define SYS_IOPRIO_GET              252
#  define SYS_INOTIFY_INIT            253
#  define SYS_INOTIFY_ADD_WATCH       254
#  define SYS_INOTIFY_RM_WATCH        255
#  define SYS_MIGRATE_PAGES           256
#  define SYS_OPENAT                  257
#  define SYS_MKDIRAT                 258
#  define SYS_MKNODAT                 259
#  define SYS_FCHOWNAT                260
#  define SYS_FUTIMESAT               261
#  define SYS_NEWFSTATAT              262
#  define SYS_UNLINKAT                263
#  define SYS_RENAMEAT                264
#  define SYS_LINKAT                  265
#  define SYS_SYMLINKAT               266
#  define SYS_READLINKAT              267
#  define SYS_FCHMODAT                268
#  define SYS_FACCESSAT               269
#  define SYS_PSELECT6                270
#  define SYS_PPOLL                   271
#  define SYS_UNSHARE                 272
#  define SYS_SET_ROBUST_LIST         273
#  define SYS_GET_ROBUST_LIST         274
#  define SYS_SPLICE                  275
#  define SYS_TEE                     276
#  define SYS_SYNC_FILE_RANGE         277
#  define SYS_VMSPLICE                278
#  define SYS_MOVE_PAGES              279
#  define SYS_UTIMENSAT               280
#  define SYS_EPOLL_PWAIT             281
#  define SYS_SIGNALFD                282
#  define SYS_TIMERFD_CREATE          283
#  define SYS_EVENTFD                 284
#  define SYS_FALLOCATE               285
#  define SYS_TIMERFD_SETTIME         286
#  define SYS_TIMERFD_GETTIME         287
#  define SYS_ACCEPT4                 288
#  define SYS_SIGNALFD4               289
#  define SYS_EVENTFD2                290
#  define SYS_EPOLL_CREATE1           291
#  define SYS_DUP3                    292
#  define SYS_PIPE2                   293
#  define SYS_INOTIFY_INIT1           294
#  define SYS_PREADV                  295
#  define SYS_PWRITEV                 296
#  define SYS_RT_TGSIGQUEUEINFO       297
#  define SYS_PERF_EVENT_OPEN         298
#  define SYS_RECVMMSG                299
#  define SYS_FANOTIFY_INIT           300
#  define SYS_FANOTIFY_MARK           301
#  define SYS_PRLIMIT64               302
#  define SYS_NAME_TO_HANDLE_AT       303
#  define SYS_OPEN_BY_HANDLE_AT       304
#  define SYS_CLOCK_ADJTIME           305
#  define SYS_SYNCFS                  306
#  define SYS_SENDMMSG                307
#  define SYS_SETNS                   308
#  define SYS_GETCPU                  309
#  define SYS_PROCESS_VM_READV        310
#  define SYS_PROCESS_VM_WRITEV       311
#  define SYS_KCMP                    312
#  define SYS_FINIT_MODULE            313
#  define SYS_SCHED_SETATTR           314
#  define SYS_SCHED_GETATTR           315
#  define SYS_RENAMEAT2               316
#  define SYS_SECCOMP                 317
#  define SYS_GETRANDOM               318
#  define SYS_MEMFD_CREATE            319
#  define SYS_KEXEC_FILE_LOAD         320
#  define SYS_BPF                     321
#  define SYS_EXECVEAT                322
#  define SYS_USERFAULTFD             323
#  define SYS_MEMBARRIER              324
#  define SYS_MLOCK2                  325
#  define SYS_COPY_FILE_RANGE         326
#  define SYS_PREADV2                 327
#  define SYS_PWRITEV2                328
#  define SYS_PKEY_MPROTECT           329
#  define SYS_PKEY_ALLOC              330
#  define SYS_PKEY_FREE               331
#  define SYS_STATX                   332
#  define SYS_IO_PGETEVENTS           333
#  define SYS_RSEQ                    334
#  define SYS_URETPROBE               335
#  define SYS_UPROBE                  336
#  define SYS_PIDFD_SEND_SIGNAL       424
#  define SYS_IO_URING_SETUP          425
#  define SYS_IO_URING_ENTER          426
#  define SYS_IO_URING_REGISTER       427
#  define SYS_OPEN_TREE               428
#  define SYS_MOVE_MOUNT              429
#  define SYS_FSOPEN                  430
#  define SYS_FSCONFIG                431
#  define SYS_FSMOUNT                 432
#  define SYS_FSPICK                  433
#  define SYS_PIDFD_OPEN              434
#  define SYS_CLONE3                  435
#  define SYS_CLOSE_RANGE             436
#  define SYS_OPENAT2                 437
#  define SYS_PIDFD_GETFD             438
#  define SYS_FACCESSAT2              439
#  define SYS_PROCESS_MADVISE         440
#  define SYS_EPOLL_PWAIT2            441
#  define SYS_MOUNT_SETATTR           442
#  define SYS_QUOTACTL_FD             443
#  define SYS_LANDLOCK_CREATE_RULESET 444
#  define SYS_LANDLOCK_ADD_RULE       445
#  define SYS_LANDLOCK_RESTRICT_SELF  446
#  define SYS_MEMFD_SECRET            447
#  define SYS_PROCESS_MRELEASE        448
#  define SYS_FUTEX_WAITV             449
#  define SYS_SET_MEMPOLICY_HOME_NODE 450
#  define SYS_CACHESTAT               451
#  define SYS_FCHMODAT2               452
#  define SYS_MAP_SHADOW_STACK        453
#  define SYS_FUTEX_WAKE              454
#  define SYS_FUTEX_WAIT              455
#  define SYS_FUTEX_REQUEUE           456
#  define SYS_STATMOUNT               457
#  define SYS_LISTMOUNT               458
#  define SYS_LSM_GET_SELF_ATTR       459
#  define SYS_LSM_SET_SELF_ATTR       460
#  define SYS_LSM_LIST_MODULES        461
#  define SYS_MSEAL                   462
#  define SYS_SETXATTRAT              463
#  define SYS_GETXATTRAT              464
#  define SYS_LISTXATTRAT             465
#  define SYS_REMOVEXATTRAT           466
#  define SYS_OPEN_TREE_ATTR          467
#  define SYS_FILE_GETATTR            468
#  define SYS_FILE_SETATTR            469
#  define SYS_LISTNS                  470
#  define SYS_RSEQ_SLICE_YIELD        471

# elif defined(__aarch64__) && defined(__linux__) && !defined(XFT_REQUIRE_LIBC)

#  ifndef AT_FDCWD
#   define AT_FDCWD                   -100
#  endif

#  define SYS_IOCTL                   29
#  define SYS_FCNTL                   25
#  define SYS_MKDIRAT                 34
#  define SYS_OPENAT                  56
#  define SYS_CLOSE                   57
#  define SYS_READ                    63
#  define SYS_WRITE                   64
#  define SYS_READV                   65
#  define SYS_WRITEV                  66
#  define SYS_NEWFSTATAT              79
#  define SYS_EXIT                    93
#  define SYS_EXIT_GROUP              94
#  define SYS_SET_TID_ADDRESS         96
#  define SYS_FUTEX                   98
#  define SYS_CLOCK_GETTIME           113
#  define SYS_SCHED_SETAFFINITY       122
#  define SYS_SCHED_GETAFFINITY       123
#  define SYS_RT_SIGPROCMASK          135
#  define SYS_GETPID                  172
#  define SYS_CLONE                   220
#  define SYS_EXECVE                  221
#  define SYS_MUNMAP                  215
#  define SYS_MREMAP                  216
#  define SYS_MMAP                    222
#  define SYS_MPROTECT                226
#  define SYS_PERF_EVENT_OPEN         241
#  define SYS_WAIT4                   260

t_i64a	xft_syscall6(t_u64a nr, const t_u64a args[6])\
		__attribute__((__nonnull__(2)));

# else

#  ifndef SYS_READ
#   define SYS_READ                         SYS_read
#  endif
#  ifndef SYS_WRITE
#   define SYS_WRITE                        SYS_write
#  endif
#  ifndef SYS_OPEN
#   define SYS_OPEN                         SYS_open
#  endif
#  ifndef SYS_CLOSE
#   define SYS_CLOSE                        SYS_close
#  endif
#  ifndef SYS_STAT
#   define SYS_STAT                         SYS_stat
#  endif
#  ifndef SYS_FSTAT
#   define SYS_FSTAT                        SYS_fstat
#  endif
#  ifndef SYS_LSTAT
#   define SYS_LSTAT                        SYS_lstat
#  endif
#  ifndef SYS_POLL
#   define SYS_POLL                         SYS_poll
#  endif
#  ifndef SYS_LSEEK
#   define SYS_LSEEK                        SYS_lseek
#  endif
#  ifndef SYS_MMAP
#   define SYS_MMAP                         SYS_mmap
#  endif
#  ifndef SYS_MPROTECT
#   define SYS_MPROTECT                     SYS_mprotect
#  endif
#  ifndef SYS_MUNMAP
#   define SYS_MUNMAP                       SYS_munmap
#  endif
#  ifndef SYS_BRK
#   define SYS_BRK                          SYS_brk
#  endif
#  ifndef SYS_RT_SIGACTION
#   define SYS_RT_SIGACTION                 SYS_rt_sigaction
#  endif
#  ifndef SYS_RT_SIGPROCMASK
#   define SYS_RT_SIGPROCMASK               SYS_rt_sigprocmask
#  endif
#  ifndef SYS_RT_SIGRETURN
#   define SYS_RT_SIGRETURN                 SYS_rt_sigreturn
#  endif
#  ifndef SYS_IOCTL
#   define SYS_IOCTL                        SYS_ioctl
#  endif
#  ifndef SYS_PREAD64
#   define SYS_PREAD64                      SYS_pread64
#  endif
#  ifndef SYS_PWRITE64
#   define SYS_PWRITE64                     SYS_pwrite64
#  endif
#  ifndef SYS_READV
#   define SYS_READV                        SYS_readv
#  endif
#  ifndef SYS_WRITEV
#   define SYS_WRITEV                       SYS_writev
#  endif
#  ifndef SYS_ACCESS
#   define SYS_ACCESS                       SYS_access
#  endif
#  ifndef SYS_PIPE
#   define SYS_PIPE                         SYS_pipe
#  endif
#  ifndef SYS_SELECT
#   define SYS_SELECT                       SYS_select
#  endif
#  ifndef SYS_SCHED_YIELD
#   define SYS_SCHED_YIELD                  SYS_sched_yield
#  endif
#  ifndef SYS_MREMAP
#   define SYS_MREMAP                       SYS_mremap
#  endif
#  ifndef SYS_MSYNC
#   define SYS_MSYNC                        SYS_msync
#  endif
#  ifndef SYS_MINCORE
#   define SYS_MINCORE                      SYS_mincore
#  endif
#  ifndef SYS_MADVISE
#   define SYS_MADVISE                      SYS_madvise
#  endif
#  ifndef SYS_SHMGET
#   define SYS_SHMGET                       SYS_shmget
#  endif
#  ifndef SYS_SHMAT
#   define SYS_SHMAT                        SYS_shmat
#  endif
#  ifndef SYS_SHMCTL
#   define SYS_SHMCTL                       SYS_shmctl
#  endif
#  ifndef SYS_DUP
#   define SYS_DUP                          SYS_dup
#  endif
#  ifndef SYS_DUP2
#   define SYS_DUP2                         SYS_dup2
#  endif
#  ifndef SYS_PAUSE
#   define SYS_PAUSE                        SYS_pause
#  endif
#  ifndef SYS_NANOSLEEP
#   define SYS_NANOSLEEP                    SYS_nanosleep
#  endif
#  ifndef SYS_GETITIMER
#   define SYS_GETITIMER                    SYS_getitimer
#  endif
#  ifndef SYS_ALARM
#   define SYS_ALARM                        SYS_alarm
#  endif
#  ifndef SYS_SETITIMER
#   define SYS_SETITIMER                    SYS_setitimer
#  endif
#  ifndef SYS_GETPID
#   define SYS_GETPID                       SYS_getpid
#  endif
#  ifndef SYS_SENDFILE
#   define SYS_SENDFILE                     SYS_sendfile
#  endif
#  ifndef SYS_SOCKET
#   define SYS_SOCKET                       SYS_socket
#  endif
#  ifndef SYS_CONNECT
#   define SYS_CONNECT                      SYS_connect
#  endif
#  ifndef SYS_ACCEPT
#   define SYS_ACCEPT                       SYS_accept
#  endif
#  ifndef SYS_SENDTO
#   define SYS_SENDTO                       SYS_sendto
#  endif
#  ifndef SYS_RECVFROM
#   define SYS_RECVFROM                     SYS_recvfrom
#  endif
#  ifndef SYS_SENDMSG
#   define SYS_SENDMSG                      SYS_sendmsg
#  endif
#  ifndef SYS_RECVMSG
#   define SYS_RECVMSG                      SYS_recvmsg
#  endif
#  ifndef SYS_SHUTDOWN
#   define SYS_SHUTDOWN                     SYS_shutdown
#  endif
#  ifndef SYS_BIND
#   define SYS_BIND                         SYS_bind
#  endif
#  ifndef SYS_LISTEN
#   define SYS_LISTEN                       SYS_listen
#  endif
#  ifndef SYS_GETSOCKNAME
#   define SYS_GETSOCKNAME                  SYS_getsockname
#  endif
#  ifndef SYS_GETPEERNAME
#   define SYS_GETPEERNAME                  SYS_getpeername
#  endif
#  ifndef SYS_SOCKETPAIR
#   define SYS_SOCKETPAIR                   SYS_socketpair
#  endif
#  ifndef SYS_SETSOCKOPT
#   define SYS_SETSOCKOPT                   SYS_setsockopt
#  endif
#  ifndef SYS_GETSOCKOPT
#   define SYS_GETSOCKOPT                   SYS_getsockopt
#  endif
#  ifndef SYS_CLONE
#   define SYS_CLONE                        SYS_clone
#  endif
#  ifndef SYS_FORK
#   define SYS_FORK                         SYS_fork
#  endif
#  ifndef SYS_VFORK
#   define SYS_VFORK                        SYS_vfork
#  endif
#  ifndef SYS_EXECVE
#   define SYS_EXECVE                       SYS_execve
#  endif
#  ifndef SYS_EXIT
#   define SYS_EXIT                         SYS_exit
#  endif
#  ifndef SYS_WAIT4
#   define SYS_WAIT4                        SYS_wait4
#  endif
#  ifndef SYS_KILL
#   define SYS_KILL                         SYS_kill
#  endif
#  ifndef SYS_UNAME
#   define SYS_UNAME                        SYS_uname
#  endif
#  ifndef SYS_SEMGET
#   define SYS_SEMGET                       SYS_semget
#  endif
#  ifndef SYS_SEMOP
#   define SYS_SEMOP                        SYS_semop
#  endif
#  ifndef SYS_SEMCTL
#   define SYS_SEMCTL                       SYS_semctl
#  endif
#  ifndef SYS_SHMDT
#   define SYS_SHMDT                        SYS_shmdt
#  endif
#  ifndef SYS_MSGGET
#   define SYS_MSGGET                       SYS_msgget
#  endif
#  ifndef SYS_MSGSND
#   define SYS_MSGSND                       SYS_msgsnd
#  endif
#  ifndef SYS_MSGRCV
#   define SYS_MSGRCV                       SYS_msgrcv
#  endif
#  ifndef SYS_MSGCTL
#   define SYS_MSGCTL                       SYS_msgctl
#  endif
#  ifndef SYS_FCNTL
#   define SYS_FCNTL                        SYS_fcntl
#  endif
#  ifndef SYS_FLOCK
#   define SYS_FLOCK                        SYS_flock
#  endif
#  ifndef SYS_FSYNC
#   define SYS_FSYNC                        SYS_fsync
#  endif
#  ifndef SYS_FDATASYNC
#   define SYS_FDATASYNC                    SYS_fdatasync
#  endif
#  ifndef SYS_TRUNCATE
#   define SYS_TRUNCATE                     SYS_truncate
#  endif
#  ifndef SYS_FTRUNCATE
#   define SYS_FTRUNCATE                    SYS_ftruncate
#  endif
#  ifndef SYS_GETDENTS
#   define SYS_GETDENTS                     SYS_getdents
#  endif
#  ifndef SYS_GETCWD
#   define SYS_GETCWD                       SYS_getcwd
#  endif
#  ifndef SYS_CHDIR
#   define SYS_CHDIR                        SYS_chdir
#  endif
#  ifndef SYS_FCHDIR
#   define SYS_FCHDIR                       SYS_fchdir
#  endif
#  ifndef SYS_RENAME
#   define SYS_RENAME                       SYS_rename
#  endif
#  ifndef SYS_MKDIR
#   define SYS_MKDIR                        SYS_mkdir
#  endif
#  ifndef SYS_RMDIR
#   define SYS_RMDIR                        SYS_rmdir
#  endif
#  ifndef SYS_CREAT
#   define SYS_CREAT                        SYS_creat
#  endif
#  ifndef SYS_LINK
#   define SYS_LINK                         SYS_link
#  endif
#  ifndef SYS_UNLINK
#   define SYS_UNLINK                       SYS_unlink
#  endif
#  ifndef SYS_SYMLINK
#   define SYS_SYMLINK                      SYS_symlink
#  endif
#  ifndef SYS_READLINK
#   define SYS_READLINK                     SYS_readlink
#  endif
#  ifndef SYS_CHMOD
#   define SYS_CHMOD                        SYS_chmod
#  endif
#  ifndef SYS_FCHMOD
#   define SYS_FCHMOD                       SYS_fchmod
#  endif
#  ifndef SYS_CHOWN
#   define SYS_CHOWN                        SYS_chown
#  endif
#  ifndef SYS_FCHOWN
#   define SYS_FCHOWN                       SYS_fchown
#  endif
#  ifndef SYS_LCHOWN
#   define SYS_LCHOWN                       SYS_lchown
#  endif
#  ifndef SYS_UMASK
#   define SYS_UMASK                        SYS_umask
#  endif
#  ifndef SYS_GETTIMEOFDAY
#   define SYS_GETTIMEOFDAY                 SYS_gettimeofday
#  endif
#  ifndef SYS_GETRLIMIT
#   define SYS_GETRLIMIT                    SYS_getrlimit
#  endif
#  ifndef SYS_GETRUSAGE
#   define SYS_GETRUSAGE                    SYS_getrusage
#  endif
#  ifndef SYS_SYSINFO
#   define SYS_SYSINFO                      SYS_sysinfo
#  endif
#  ifndef SYS_TIMES
#   define SYS_TIMES                        SYS_times
#  endif
#  ifndef SYS_PTRACE
#   define SYS_PTRACE                       SYS_ptrace
#  endif
#  ifndef SYS_GETUID
#   define SYS_GETUID                       SYS_getuid
#  endif
#  ifndef SYS_SYSLOG
#   define SYS_SYSLOG                       SYS_syslog
#  endif
#  ifndef SYS_GETGID
#   define SYS_GETGID                       SYS_getgid
#  endif
#  ifndef SYS_SETUID
#   define SYS_SETUID                       SYS_setuid
#  endif
#  ifndef SYS_SETGID
#   define SYS_SETGID                       SYS_setgid
#  endif
#  ifndef SYS_GETEUID
#   define SYS_GETEUID                      SYS_geteuid
#  endif
#  ifndef SYS_GETEGID
#   define SYS_GETEGID                      SYS_getegid
#  endif
#  ifndef SYS_SETPGID
#   define SYS_SETPGID                      SYS_setpgid
#  endif
#  ifndef SYS_GETPPID
#   define SYS_GETPPID                      SYS_getppid
#  endif
#  ifndef SYS_GETPGRP
#   define SYS_GETPGRP                      SYS_getpgrp
#  endif
#  ifndef SYS_SETSID
#   define SYS_SETSID                       SYS_setsid
#  endif
#  ifndef SYS_SETREUID
#   define SYS_SETREUID                     SYS_setreuid
#  endif
#  ifndef SYS_SETREGID
#   define SYS_SETREGID                     SYS_setregid
#  endif
#  ifndef SYS_GETGROUPS
#   define SYS_GETGROUPS                    SYS_getgroups
#  endif
#  ifndef SYS_SETGROUPS
#   define SYS_SETGROUPS                    SYS_setgroups
#  endif
#  ifndef SYS_SETRESUID
#   define SYS_SETRESUID                    SYS_setresuid
#  endif
#  ifndef SYS_GETRESUID
#   define SYS_GETRESUID                    SYS_getresuid
#  endif
#  ifndef SYS_SETRESGID
#   define SYS_SETRESGID                    SYS_setresgid
#  endif
#  ifndef SYS_GETRESGID
#   define SYS_GETRESGID                    SYS_getresgid
#  endif
#  ifndef SYS_GETPGID
#   define SYS_GETPGID                      SYS_getpgid
#  endif
#  ifndef SYS_SETFSUID
#   define SYS_SETFSUID                     SYS_setfsuid
#  endif
#  ifndef SYS_SETFSGID
#   define SYS_SETFSGID                     SYS_setfsgid
#  endif
#  ifndef SYS_GETSID
#   define SYS_GETSID                       SYS_getsid
#  endif
#  ifndef SYS_CAPGET
#   define SYS_CAPGET                       SYS_capget
#  endif
#  ifndef SYS_CAPSET
#   define SYS_CAPSET                       SYS_capset
#  endif
#  ifndef SYS_RT_SIGPENDING
#   define SYS_RT_SIGPENDING                SYS_rt_sigpending
#  endif
#  ifndef SYS_RT_SIGTIMEDWAIT
#   define SYS_RT_SIGTIMEDWAIT              SYS_rt_sigtimedwait
#  endif
#  ifndef SYS_RT_SIGQUEUEINFO
#   define SYS_RT_SIGQUEUEINFO              SYS_rt_sigqueueinfo
#  endif
#  ifndef SYS_RT_SIGSUSPEND
#   define SYS_RT_SIGSUSPEND                SYS_rt_sigsuspend
#  endif
#  ifndef SYS_SIGALTSTACK
#   define SYS_SIGALTSTACK                  SYS_sigaltstack
#  endif
#  ifndef SYS_UTIME
#   define SYS_UTIME                        SYS_utime
#  endif
#  ifndef SYS_MKNOD
#   define SYS_MKNOD                        SYS_mknod
#  endif
#  ifndef SYS_USELIB
#   define SYS_USELIB                       SYS_uselib
#  endif
#  ifndef SYS_PERSONALITY
#   define SYS_PERSONALITY                  SYS_personality
#  endif
#  ifndef SYS_USTAT
#   define SYS_USTAT                        SYS_ustat
#  endif
#  ifndef SYS_STATFS
#   define SYS_STATFS                       SYS_statfs
#  endif
#  ifndef SYS_FSTATFS
#   define SYS_FSTATFS                      SYS_fstatfs
#  endif
#  ifndef SYS_SYSFS
#   define SYS_SYSFS                        SYS_sysfs
#  endif
#  ifndef SYS_GETPRIORITY
#   define SYS_GETPRIORITY                  SYS_getpriority
#  endif
#  ifndef SYS_SETPRIORITY
#   define SYS_SETPRIORITY                  SYS_setpriority
#  endif
#  ifndef SYS_SCHED_SETPARAM
#   define SYS_SCHED_SETPARAM               SYS_sched_setparam
#  endif
#  ifndef SYS_SCHED_GETPARAM
#   define SYS_SCHED_GETPARAM               SYS_sched_getparam
#  endif
#  ifndef SYS_SCHED_SETSCHEDULER
#   define SYS_SCHED_SETSCHEDULER           SYS_sched_setscheduler
#  endif
#  ifndef SYS_SCHED_GETSCHEDULER
#   define SYS_SCHED_GETSCHEDULER           SYS_sched_getscheduler
#  endif
#  ifndef SYS_SCHED_GET_PRIORITY_MAX
#   define SYS_SCHED_GET_PRIORITY_MAX       SYS_sched_get_priority_max
#  endif
#  ifndef SYS_SCHED_GET_PRIORITY_MIN
#   define SYS_SCHED_GET_PRIORITY_MIN       SYS_sched_get_priority_min
#  endif
#  ifndef SYS_SCHED_RR_GET_INTERVAL
#   define SYS_SCHED_RR_GET_INTERVAL        SYS_sched_rr_get_interval
#  endif
#  ifndef SYS_MLOCK
#   define SYS_MLOCK                        SYS_mlock
#  endif
#  ifndef SYS_MUNLOCK
#   define SYS_MUNLOCK                      SYS_munlock
#  endif
#  ifndef SYS_MLOCKALL
#   define SYS_MLOCKALL                     SYS_mlockall
#  endif
#  ifndef SYS_MUNLOCKALL
#   define SYS_MUNLOCKALL                   SYS_munlockall
#  endif
#  ifndef SYS_VHANGUP
#   define SYS_VHANGUP                      SYS_vhangup
#  endif
#  ifndef SYS_MODIFY_LDT
#   define SYS_MODIFY_LDT                   SYS_modify_ldt
#  endif
#  ifndef SYS_PIVOT_ROOT
#   define SYS_PIVOT_ROOT                   SYS_pivot_root
#  endif
#  ifndef SYS__SYSCTL
#   define SYS__SYSCTL                      SYS__sysctl
#  endif
#  ifndef SYS_PRCTL
#   define SYS_PRCTL                        SYS_prctl
#  endif
#  ifndef SYS_ARCH_PRCTL
#   define SYS_ARCH_PRCTL                   SYS_arch_prctl
#  endif
#  ifndef SYS_ADJTIMEX
#   define SYS_ADJTIMEX                     SYS_adjtimex
#  endif
#  ifndef SYS_SETRLIMIT
#   define SYS_SETRLIMIT                    SYS_setrlimit
#  endif
#  ifndef SYS_CHROOT
#   define SYS_CHROOT                       SYS_chroot
#  endif
#  ifndef SYS_SYNC
#   define SYS_SYNC                         SYS_sync
#  endif
#  ifndef SYS_ACCT
#   define SYS_ACCT                         SYS_acct
#  endif
#  ifndef SYS_SETTIMEOFDAY
#   define SYS_SETTIMEOFDAY                 SYS_settimeofday
#  endif
#  ifndef SYS_MOUNT
#   define SYS_MOUNT                        SYS_mount
#  endif
#  ifndef SYS_UMOUNT2
#   define SYS_UMOUNT2                      SYS_umount2
#  endif
#  ifndef SYS_SWAPON
#   define SYS_SWAPON                       SYS_swapon
#  endif
#  ifndef SYS_SWAPOFF
#   define SYS_SWAPOFF                      SYS_swapoff
#  endif
#  ifndef SYS_REBOOT
#   define SYS_REBOOT                       SYS_reboot
#  endif
#  ifndef SYS_SETHOSTNAME
#   define SYS_SETHOSTNAME                  SYS_sethostname
#  endif
#  ifndef SYS_SETDOMAINNAME
#   define SYS_SETDOMAINNAME                SYS_setdomainname
#  endif
#  ifndef SYS_IOPL
#   define SYS_IOPL                         SYS_iopl
#  endif
#  ifndef SYS_IOPERM
#   define SYS_IOPERM                       SYS_ioperm
#  endif
#  ifndef SYS_CREATE_MODULE
#   define SYS_CREATE_MODULE                SYS_create_module
#  endif
#  ifndef SYS_INIT_MODULE
#   define SYS_INIT_MODULE                  SYS_init_module
#  endif
#  ifndef SYS_DELETE_MODULE
#   define SYS_DELETE_MODULE                SYS_delete_module
#  endif
#  ifndef SYS_GET_KERNEL_SYMS
#   define SYS_GET_KERNEL_SYMS              SYS_get_kernel_syms
#  endif
#  ifndef SYS_QUERY_MODULE
#   define SYS_QUERY_MODULE                 SYS_query_module
#  endif
#  ifndef SYS_QUOTACTL
#   define SYS_QUOTACTL                     SYS_quotactl
#  endif
#  ifndef SYS_NFSSERVCTL
#   define SYS_NFSSERVCTL                   SYS_nfsservctl
#  endif
#  ifndef SYS_GETPMSG
#   define SYS_GETPMSG                      SYS_getpmsg
#  endif
#  ifndef SYS_PUTPMSG
#   define SYS_PUTPMSG                      SYS_putpmsg
#  endif
#  ifndef SYS_AFS_SYSCALL
#   define SYS_AFS_SYSCALL                  SYS_afs_syscall
#  endif
#  ifndef SYS_TUXCALL
#   define SYS_TUXCALL                      SYS_tuxcall
#  endif
#  ifndef SYS_SECURITY
#   define SYS_SECURITY                     SYS_security
#  endif
#  ifndef SYS_GETTID
#   define SYS_GETTID                       SYS_gettid
#  endif
#  ifndef SYS_READAHEAD
#   define SYS_READAHEAD                    SYS_readahead
#  endif
#  ifndef SYS_SETXATTR
#   define SYS_SETXATTR                     SYS_setxattr
#  endif
#  ifndef SYS_LSETXATTR
#   define SYS_LSETXATTR                    SYS_lsetxattr
#  endif
#  ifndef SYS_FSETXATTR
#   define SYS_FSETXATTR                    SYS_fsetxattr
#  endif
#  ifndef SYS_GETXATTR
#   define SYS_GETXATTR                     SYS_getxattr
#  endif
#  ifndef SYS_LGETXATTR
#   define SYS_LGETXATTR                    SYS_lgetxattr
#  endif
#  ifndef SYS_FGETXATTR
#   define SYS_FGETXATTR                    SYS_fgetxattr
#  endif
#  ifndef SYS_LISTXATTR
#   define SYS_LISTXATTR                    SYS_listxattr
#  endif
#  ifndef SYS_LLISTXATTR
#   define SYS_LLISTXATTR                   SYS_llistxattr
#  endif
#  ifndef SYS_FLISTXATTR
#   define SYS_FLISTXATTR                   SYS_flistxattr
#  endif
#  ifndef SYS_REMOVEXATTR
#   define SYS_REMOVEXATTR                  SYS_removexattr
#  endif
#  ifndef SYS_LREMOVEXATTR
#   define SYS_LREMOVEXATTR                 SYS_lremovexattr
#  endif
#  ifndef SYS_FREMOVEXATTR
#   define SYS_FREMOVEXATTR                 SYS_fremovexattr
#  endif
#  ifndef SYS_TKILL
#   define SYS_TKILL                        SYS_tkill
#  endif
#  ifndef SYS_TIME
#   define SYS_TIME                         SYS_time
#  endif
#  ifndef SYS_FUTEX
#   define SYS_FUTEX                        SYS_futex
#  endif
#  ifndef SYS_SCHED_SETAFFINITY
#   define SYS_SCHED_SETAFFINITY            SYS_sched_setaffinity
#  endif
#  ifndef SYS_SCHED_GETAFFINITY
#   define SYS_SCHED_GETAFFINITY            SYS_sched_getaffinity
#  endif
#  ifndef SYS_SET_THREAD_AREA
#   define SYS_SET_THREAD_AREA              SYS_set_thread_area
#  endif
#  ifndef SYS_IO_SETUP
#   define SYS_IO_SETUP                     SYS_io_setup
#  endif
#  ifndef SYS_IO_DESTROY
#   define SYS_IO_DESTROY                   SYS_io_destroy
#  endif
#  ifndef SYS_IO_GETEVENTS
#   define SYS_IO_GETEVENTS                 SYS_io_getevents
#  endif
#  ifndef SYS_IO_SUBMIT
#   define SYS_IO_SUBMIT                    SYS_io_submit
#  endif
#  ifndef SYS_IO_CANCEL
#   define SYS_IO_CANCEL                    SYS_io_cancel
#  endif
#  ifndef SYS_GET_THREAD_AREA
#   define SYS_GET_THREAD_AREA              SYS_get_thread_area
#  endif
#  ifndef SYS_LOOKUP_DCOOKIE
#   define SYS_LOOKUP_DCOOKIE               SYS_lookup_dcookie
#  endif
#  ifndef SYS_EPOLL_CREATE
#   define SYS_EPOLL_CREATE                 SYS_epoll_create
#  endif
#  ifndef SYS_EPOLL_CTL_OLD
#   define SYS_EPOLL_CTL_OLD                SYS_epoll_ctl_old
#  endif
#  ifndef SYS_EPOLL_WAIT_OLD
#   define SYS_EPOLL_WAIT_OLD               SYS_epoll_wait_old
#  endif
#  ifndef SYS_REMAP_FILE_PAGES
#   define SYS_REMAP_FILE_PAGES             SYS_remap_file_pages
#  endif
#  ifndef SYS_GETDENTS64
#   define SYS_GETDENTS64                   SYS_getdents64
#  endif
#  ifndef SYS_SET_TID_ADDRESS
#   define SYS_SET_TID_ADDRESS              SYS_set_tid_address
#  endif
#  ifndef SYS_RESTART_SYSCALL
#   define SYS_RESTART_SYSCALL              SYS_restart_syscall
#  endif
#  ifndef SYS_SEMTIMEDOP
#   define SYS_SEMTIMEDOP                   SYS_semtimedop
#  endif
#  ifndef SYS_FADVISE64
#   define SYS_FADVISE64                    SYS_fadvise64
#  endif
#  ifndef SYS_TIMER_CREATE
#   define SYS_TIMER_CREATE                 SYS_timer_create
#  endif
#  ifndef SYS_TIMER_SETTIME
#   define SYS_TIMER_SETTIME                SYS_timer_settime
#  endif
#  ifndef SYS_TIMER_GETTIME
#   define SYS_TIMER_GETTIME                SYS_timer_gettime
#  endif
#  ifndef SYS_TIMER_GETOVERRUN
#   define SYS_TIMER_GETOVERRUN             SYS_timer_getoverrun
#  endif
#  ifndef SYS_TIMER_DELETE
#   define SYS_TIMER_DELETE                 SYS_timer_delete
#  endif
#  ifndef SYS_CLOCK_SETTIME
#   define SYS_CLOCK_SETTIME                SYS_clock_settime
#  endif
#  ifndef SYS_CLOCK_GETTIME
#   define SYS_CLOCK_GETTIME                SYS_clock_gettime
#  endif
#  ifndef SYS_CLOCK_GETRES
#   define SYS_CLOCK_GETRES                 SYS_clock_getres
#  endif
#  ifndef SYS_CLOCK_NANOSLEEP
#   define SYS_CLOCK_NANOSLEEP              SYS_clock_nanosleep
#  endif
#  ifndef SYS_EXIT_GROUP
#   define SYS_EXIT_GROUP                   SYS_exit_group
#  endif
#  ifndef SYS_EPOLL_WAIT
#   define SYS_EPOLL_WAIT                   SYS_epoll_wait
#  endif
#  ifndef SYS_EPOLL_CTL
#   define SYS_EPOLL_CTL                    SYS_epoll_ctl
#  endif
#  ifndef SYS_TGKILL
#   define SYS_TGKILL                       SYS_tgkill
#  endif
#  ifndef SYS_UTIMES
#   define SYS_UTIMES                       SYS_utimes
#  endif
#  ifndef SYS_VSERVER
#   define SYS_VSERVER                      SYS_vserver
#  endif
#  ifndef SYS_MBIND
#   define SYS_MBIND                        SYS_mbind
#  endif
#  ifndef SYS_SET_MEMPOLICY
#   define SYS_SET_MEMPOLICY                SYS_set_mempolicy
#  endif
#  ifndef SYS_GET_MEMPOLICY
#   define SYS_GET_MEMPOLICY                SYS_get_mempolicy
#  endif
#  ifndef SYS_MQ_OPEN
#   define SYS_MQ_OPEN                      SYS_mq_open
#  endif
#  ifndef SYS_MQ_UNLINK
#   define SYS_MQ_UNLINK                    SYS_mq_unlink
#  endif
#  ifndef SYS_MQ_TIMEDSEND
#   define SYS_MQ_TIMEDSEND                 SYS_mq_timedsend
#  endif
#  ifndef SYS_MQ_TIMEDRECEIVE
#   define SYS_MQ_TIMEDRECEIVE              SYS_mq_timedreceive
#  endif
#  ifndef SYS_MQ_NOTIFY
#   define SYS_MQ_NOTIFY                    SYS_mq_notify
#  endif
#  ifndef SYS_MQ_GETSETATTR
#   define SYS_MQ_GETSETATTR                SYS_mq_getsetattr
#  endif
#  ifndef SYS_KEXEC_LOAD
#   define SYS_KEXEC_LOAD                   SYS_kexec_load
#  endif
#  ifndef SYS_WAITID
#   define SYS_WAITID                       SYS_waitid
#  endif
#  ifndef SYS_ADD_KEY
#   define SYS_ADD_KEY                      SYS_add_key
#  endif
#  ifndef SYS_REQUEST_KEY
#   define SYS_REQUEST_KEY                  SYS_request_key
#  endif
#  ifndef SYS_KEYCTL
#   define SYS_KEYCTL                       SYS_keyctl
#  endif
#  ifndef SYS_IOPRIO_SET
#   define SYS_IOPRIO_SET                   SYS_ioprio_set
#  endif
#  ifndef SYS_IOPRIO_GET
#   define SYS_IOPRIO_GET                   SYS_ioprio_get
#  endif
#  ifndef SYS_INOTIFY_INIT
#   define SYS_INOTIFY_INIT                 SYS_inotify_init
#  endif
#  ifndef SYS_INOTIFY_ADD_WATCH
#   define SYS_INOTIFY_ADD_WATCH            SYS_inotify_add_watch
#  endif
#  ifndef SYS_INOTIFY_RM_WATCH
#   define SYS_INOTIFY_RM_WATCH             SYS_inotify_rm_watch
#  endif
#  ifndef SYS_MIGRATE_PAGES
#   define SYS_MIGRATE_PAGES                SYS_migrate_pages
#  endif
#  ifndef SYS_OPENAT
#   define SYS_OPENAT                       SYS_openat
#  endif
#  ifndef SYS_MKDIRAT
#   define SYS_MKDIRAT                      SYS_mkdirat
#  endif
#  ifndef SYS_MKNODAT
#   define SYS_MKNODAT                      SYS_mknodat
#  endif
#  ifndef SYS_FCHOWNAT
#   define SYS_FCHOWNAT                     SYS_fchownat
#  endif
#  ifndef SYS_FUTIMESAT
#   define SYS_FUTIMESAT                    SYS_futimesat
#  endif
#  ifndef SYS_NEWFSTATAT
#   define SYS_NEWFSTATAT                   SYS_newfstatat
#  endif
#  ifndef SYS_UNLINKAT
#   define SYS_UNLINKAT                     SYS_unlinkat
#  endif
#  ifndef SYS_RENAMEAT
#   define SYS_RENAMEAT                     SYS_renameat
#  endif
#  ifndef SYS_LINKAT
#   define SYS_LINKAT                       SYS_linkat
#  endif
#  ifndef SYS_SYMLINKAT
#   define SYS_SYMLINKAT                    SYS_symlinkat
#  endif
#  ifndef SYS_READLINKAT
#   define SYS_READLINKAT                   SYS_readlinkat
#  endif
#  ifndef SYS_FCHMODAT
#   define SYS_FCHMODAT                     SYS_fchmodat
#  endif
#  ifndef SYS_FACCESSAT
#   define SYS_FACCESSAT                    SYS_faccessat
#  endif
#  ifndef SYS_PSELECT6
#   define SYS_PSELECT6                     SYS_pselect6
#  endif
#  ifndef SYS_PPOLL
#   define SYS_PPOLL                        SYS_ppoll
#  endif
#  ifndef SYS_UNSHARE
#   define SYS_UNSHARE                      SYS_unshare
#  endif
#  ifndef SYS_SET_ROBUST_LIST
#   define SYS_SET_ROBUST_LIST              SYS_set_robust_list
#  endif
#  ifndef SYS_GET_ROBUST_LIST
#   define SYS_GET_ROBUST_LIST              SYS_get_robust_list
#  endif
#  ifndef SYS_SPLICE
#   define SYS_SPLICE                       SYS_splice
#  endif
#  ifndef SYS_TEE
#   define SYS_TEE                          SYS_tee
#  endif
#  ifndef SYS_SYNC_FILE_RANGE
#   define SYS_SYNC_FILE_RANGE              SYS_sync_file_range
#  endif
#  ifndef SYS_VMSPLICE
#   define SYS_VMSPLICE                     SYS_vmsplice
#  endif
#  ifndef SYS_MOVE_PAGES
#   define SYS_MOVE_PAGES                   SYS_move_pages
#  endif
#  ifndef SYS_UTIMENSAT
#   define SYS_UTIMENSAT                    SYS_utimensat
#  endif
#  ifndef SYS_EPOLL_PWAIT
#   define SYS_EPOLL_PWAIT                  SYS_epoll_pwait
#  endif
#  ifndef SYS_SIGNALFD
#   define SYS_SIGNALFD                     SYS_signalfd
#  endif
#  ifndef SYS_TIMERFD_CREATE
#   define SYS_TIMERFD_CREATE               SYS_timerfd_create
#  endif
#  ifndef SYS_EVENTFD
#   define SYS_EVENTFD                      SYS_eventfd
#  endif
#  ifndef SYS_FALLOCATE
#   define SYS_FALLOCATE                    SYS_fallocate
#  endif
#  ifndef SYS_TIMERFD_SETTIME
#   define SYS_TIMERFD_SETTIME              SYS_timerfd_settime
#  endif
#  ifndef SYS_TIMERFD_GETTIME
#   define SYS_TIMERFD_GETTIME              SYS_timerfd_gettime
#  endif
#  ifndef SYS_ACCEPT4
#   define SYS_ACCEPT4                      SYS_accept4
#  endif
#  ifndef SYS_SIGNALFD4
#   define SYS_SIGNALFD4                    SYS_signalfd4
#  endif
#  ifndef SYS_EVENTFD2
#   define SYS_EVENTFD2                     SYS_eventfd2
#  endif
#  ifndef SYS_EPOLL_CREATE1
#   define SYS_EPOLL_CREATE1                SYS_epoll_create1
#  endif
#  ifndef SYS_DUP3
#   define SYS_DUP3                         SYS_dup3
#  endif
#  ifndef SYS_PIPE2
#   define SYS_PIPE2                        SYS_pipe2
#  endif
#  ifndef SYS_INOTIFY_INIT1
#   define SYS_INOTIFY_INIT1                SYS_inotify_init1
#  endif
#  ifndef SYS_PREADV
#   define SYS_PREADV                       SYS_preadv
#  endif
#  ifndef SYS_PWRITEV
#   define SYS_PWRITEV                      SYS_pwritev
#  endif
#  ifndef SYS_RT_TGSIGQUEUEINFO
#   define SYS_RT_TGSIGQUEUEINFO            SYS_rt_tgsigqueueinfo
#  endif
#  ifndef SYS_PERF_EVENT_OPEN
#   define SYS_PERF_EVENT_OPEN              SYS_perf_event_open
#  endif
#  ifndef SYS_RECVMMSG
#   define SYS_RECVMMSG                     SYS_recvmmsg
#  endif
#  ifndef SYS_FANOTIFY_INIT
#   define SYS_FANOTIFY_INIT                SYS_fanotify_init
#  endif
#  ifndef SYS_FANOTIFY_MARK
#   define SYS_FANOTIFY_MARK                SYS_fanotify_mark
#  endif
#  ifndef SYS_PRLIMIT64
#   define SYS_PRLIMIT64                    SYS_prlimit64
#  endif
#  ifndef SYS_NAME_TO_HANDLE_AT
#   define SYS_NAME_TO_HANDLE_AT            SYS_name_to_handle_at
#  endif
#  ifndef SYS_OPEN_BY_HANDLE_AT
#   define SYS_OPEN_BY_HANDLE_AT            SYS_open_by_handle_at
#  endif
#  ifndef SYS_CLOCK_ADJTIME
#   define SYS_CLOCK_ADJTIME                SYS_clock_adjtime
#  endif
#  ifndef SYS_SYNCFS
#   define SYS_SYNCFS                       SYS_syncfs
#  endif
#  ifndef SYS_SENDMMSG
#   define SYS_SENDMMSG                     SYS_sendmmsg
#  endif
#  ifndef SYS_SETNS
#   define SYS_SETNS                        SYS_setns
#  endif
#  ifndef SYS_GETCPU
#   define SYS_GETCPU                       SYS_getcpu
#  endif
#  ifndef SYS_PROCESS_VM_READV
#   define SYS_PROCESS_VM_READV             SYS_process_vm_readv
#  endif
#  ifndef SYS_PROCESS_VM_WRITEV
#   define SYS_PROCESS_VM_WRITEV            SYS_process_vm_writev
#  endif
#  ifndef SYS_KCMP
#   define SYS_KCMP                         SYS_kcmp
#  endif
#  ifndef SYS_FINIT_MODULE
#   define SYS_FINIT_MODULE                 SYS_finit_module
#  endif
#  ifndef SYS_SCHED_SETATTR
#   define SYS_SCHED_SETATTR                SYS_sched_setattr
#  endif
#  ifndef SYS_SCHED_GETATTR
#   define SYS_SCHED_GETATTR                SYS_sched_getattr
#  endif
#  ifndef SYS_RENAMEAT2
#   define SYS_RENAMEAT2                    SYS_renameat2
#  endif
#  ifndef SYS_SECCOMP
#   define SYS_SECCOMP                      SYS_seccomp
#  endif
#  ifndef SYS_GETRANDOM
#   define SYS_GETRANDOM                    SYS_getrandom
#  endif
#  ifndef SYS_MEMFD_CREATE
#   define SYS_MEMFD_CREATE                 SYS_memfd_create
#  endif
#  ifndef SYS_KEXEC_FILE_LOAD
#   define SYS_KEXEC_FILE_LOAD              SYS_kexec_file_load
#  endif
#  ifndef SYS_BPF
#   define SYS_BPF                          SYS_bpf
#  endif
#  ifndef SYS_EXECVEAT
#   define SYS_EXECVEAT                     SYS_execveat
#  endif
#  ifndef SYS_USERFAULTFD
#   define SYS_USERFAULTFD                  SYS_userfaultfd
#  endif
#  ifndef SYS_MEMBARRIER
#   define SYS_MEMBARRIER                   SYS_membarrier
#  endif
#  ifndef SYS_MLOCK2
#   define SYS_MLOCK2                       SYS_mlock2
#  endif
#  ifndef SYS_COPY_FILE_RANGE
#   define SYS_COPY_FILE_RANGE              SYS_copy_file_range
#  endif
#  ifndef SYS_PREADV2
#   define SYS_PREADV2                      SYS_preadv2
#  endif
#  ifndef SYS_PWRITEV2
#   define SYS_PWRITEV2                     SYS_pwritev2
#  endif
#  ifndef SYS_PKEY_MPROTECT
#   define SYS_PKEY_MPROTECT                SYS_pkey_mprotect
#  endif
#  ifndef SYS_PKEY_ALLOC
#   define SYS_PKEY_ALLOC                   SYS_pkey_alloc
#  endif
#  ifndef SYS_PKEY_FREE
#   define SYS_PKEY_FREE                    SYS_pkey_free
#  endif
#  ifndef SYS_STATX
#   define SYS_STATX                        SYS_statx
#  endif
#  ifndef SYS_IO_PGETEVENTS
#   define SYS_IO_PGETEVENTS                SYS_io_pgetevents
#  endif
#  ifndef SYS_RSEQ
#   define SYS_RSEQ                         SYS_rseq
#  endif
#  ifndef SYS_PIDFD_SEND_SIGNAL
#   define SYS_PIDFD_SEND_SIGNAL            SYS_pidfd_send_signal
#  endif
#  ifndef SYS_IO_URING_SETUP
#   define SYS_IO_URING_SETUP               SYS_io_uring_setup
#  endif
#  ifndef SYS_IO_URING_ENTER
#   define SYS_IO_URING_ENTER               SYS_io_uring_enter
#  endif
#  ifndef SYS_IO_URING_REGISTER
#   define SYS_IO_URING_REGISTER            SYS_io_uring_register
#  endif
#  ifndef SYS_OPEN_TREE
#   define SYS_OPEN_TREE                    SYS_open_tree
#  endif
#  ifndef SYS_MOVE_MOUNT
#   define SYS_MOVE_MOUNT                   SYS_move_mount
#  endif
#  ifndef SYS_FSOPEN
#   define SYS_FSOPEN                       SYS_fsopen
#  endif
#  ifndef SYS_FSCONFIG
#   define SYS_FSCONFIG                     SYS_fsconfig
#  endif
#  ifndef SYS_FSMOUNT
#   define SYS_FSMOUNT                      SYS_fsmount
#  endif
#  ifndef SYS_FSPICK
#   define SYS_FSPICK                       SYS_fspick
#  endif
#  ifndef SYS_PIDFD_OPEN
#   define SYS_PIDFD_OPEN                   SYS_pidfd_open
#  endif
#  ifndef SYS_CLONE3
#   define SYS_CLONE3                       SYS_clone3
#  endif
#  ifndef SYS_CLOSE_RANGE
#   define SYS_CLOSE_RANGE                  SYS_close_range
#  endif
#  ifndef SYS_OPENAT2
#   define SYS_OPENAT2                      SYS_openat2
#  endif
#  ifndef SYS_PIDFD_GETFD
#   define SYS_PIDFD_GETFD                  SYS_pidfd_getfd
#  endif
#  ifndef SYS_FACCESSAT2
#   define SYS_FACCESSAT2                   SYS_faccessat2
#  endif
#  ifndef SYS_PROCESS_MADVISE
#   define SYS_PROCESS_MADVISE              SYS_process_madvise
#  endif
#  ifndef SYS_EPOLL_PWAIT2
#   define SYS_EPOLL_PWAIT2                 SYS_epoll_pwait2
#  endif
#  ifndef SYS_MOUNT_SETATTR
#   define SYS_MOUNT_SETATTR                SYS_mount_setattr
#  endif
#  ifndef SYS_QUOTACTL_FD
#   define SYS_QUOTACTL_FD                  SYS_quotactl_fd
#  endif
#  ifndef SYS_LANDLOCK_CREATE_RULESET
#   define SYS_LANDLOCK_CREATE_RULESET      SYS_landlock_create_ruleset
#  endif
#  ifndef SYS_LANDLOCK_ADD_RULE
#   define SYS_LANDLOCK_ADD_RULE            SYS_landlock_add_rule
#  endif
#  ifndef SYS_LANDLOCK_RESTRICT_SELF
#   define SYS_LANDLOCK_RESTRICT_SELF       SYS_landlock_restrict_self
#  endif
#  ifndef SYS_MEMFD_SECRET
#   define SYS_MEMFD_SECRET                 SYS_memfd_secret
#  endif
#  ifndef SYS_PROCESS_MRELEASE
#   define SYS_PROCESS_MRELEASE             SYS_process_mrelease
#  endif
#  ifndef SYS_FUTEX_WAITV
#   define SYS_FUTEX_WAITV                  SYS_futex_waitv
#  endif
#  ifndef SYS_SET_MEMPOLICY_HOME_NODE
#   define SYS_SET_MEMPOLICY_HOME_NODE      SYS_set_mempolicy_home_node
#  endif
#  ifndef SYS_CACHESTAT
#   define SYS_CACHESTAT                    SYS_cachestat
#  endif
#  ifndef SYS_FCHMODAT2
#   define SYS_FCHMODAT2                    SYS_fchmodat2
#  endif
#  ifndef SYS_MAP_SHADOW_STACK
#   define SYS_MAP_SHADOW_STACK             SYS_map_shadow_stack
#  endif
#  ifndef SYS_FUTEX_WAKE
#   define SYS_FUTEX_WAKE                   SYS_futex_wake
#  endif
#  ifndef SYS_FUTEX_WAIT
#   define SYS_FUTEX_WAIT                   SYS_futex_wait
#  endif
#  ifndef SYS_FUTEX_REQUEUE
#   define SYS_FUTEX_REQUEUE                SYS_futex_requeue
#  endif
#  ifndef SYS_STATMOUNT
#   define SYS_STATMOUNT                    SYS_statmount
#  endif
#  ifndef SYS_LISTMOUNT
#   define SYS_LISTMOUNT                    SYS_listmount
#  endif
#  ifndef SYS_LSM_GET_SELF_ATTR
#   define SYS_LSM_GET_SELF_ATTR            SYS_lsm_get_self_attr
#  endif
#  ifndef SYS_LSM_SET_SELF_ATTR
#   define SYS_LSM_SET_SELF_ATTR            SYS_lsm_set_self_attr
#  endif
#  ifndef SYS_LSM_LIST_MODULES
#   define SYS_LSM_LIST_MODULES             SYS_lsm_list_modules
#  endif

# endif

#endif
