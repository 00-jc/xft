# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/18 03:43:49 by jaicastr          #+#    #+#              #
#    Updated: 2026/05/20 09:41:36 by jaicastr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       := libxft.a
OBJDIR     := build

CC_CLANG   := clang
CC_GCC     := gcc
CC_ID	   := $(shell $(CC) --version 2>/dev/null | head -1)
MAXTHREADS := $(shell nproc)
LLC 	   := $(shell getconf LEVEL3_CACHE_SIZE)
SCANNER    := scan-build

MARCH      := -march=native
INCLUDES   := -Iinclude


WARNS_COMMON := -Wall -Wextra -Werror -Wpedantic -std=c23                      \
	-fstrict-aliasing -Wstrict-aliasing                                        \
	-Wshadow                                                                   \
	-Waddress                                                                  \
	-Wattributes                                                               \
	-Wredundant-decls                                                          \
	-Wstrict-prototypes                                                        \
	-Wmissing-prototypes                                                       \
	-Wold-style-definition                                                     \
	-Wnull-dereference                                                         \
	-Wundef                                                                    \
	-Wformat-security                                                          \
	-Wformat=2                                                                 \
	-Wformat-nonliteral                                                        \
	-Wwrite-strings                                                            \
	-Wuninitialized                                                            \
	-Wpointer-arith                                                            \
	-Wunused                                                                   \
	-Wtautological-compare                                                     \
	-Wvla                                                                      \
	-Wignored-qualifiers                                                       \
	-Wnonnull                                                                  \
	-Winfinite-recursion                                                       \
	-Wimplicit                                                                 \
	-Wimplicit-fallthrough                                                     \
	-Wmissing-braces                                                           \
	-Wmissing-include-dirs                                                     \
	-Wparentheses                                                              \
	-Wshift-negative-value                                                     \
	-Wmisleading-indentation                                                   \
	-Wfloat-equal                                                              \
	-Wdangling-else                                                            \
	-Wmissing-noreturn                                                         \
	-Wchar-subscripts                                                          \
	-Wsequence-point                                                           \
	-Wbool-operation                                                           \
	-Wunreachable-code                                                         \
	-Wformat-overflow                                                          \
	-Wformat-truncation                                                        \
	-Wcast-function-type
	# -Wdouble-promotion                                                         \

WARNS_CLANG := $(WARNS_COMMON)                                                \
	-Wbitwise-instead-of-logical                                               \
	-Wnull-pointer-arithmetic                                                  \
	-Wcast-function-type-strict                                                \
	-Wambiguous-ellipsis                                                       \
	-Wambiguous-macro                                                          \
	-Wassume                                                                   \
	-Wpessimizing-move                                                         \
	-Wgnu-union-cast                                                           \
	-Wlanguage-extension-token                                                 \
	-Wgnu-statement-expression-from-macro-expansion                            \
	-Wbounds-safety-counted-by-elt-type-unknown-size                           \
	-Wcast-function-type-mismatch                                              \
	-Wc99-compat                                                               \
	-Wbool-conversions                                                         \
	-Wbitfield-enum-conversion                                                 \
	-Warray-bounds-pointer-arithmetic                                          \
	-Wloop-analysis                                                            \
	-Wcomma                                                                    \
	-Wover-aligned                                                             \
	-Wconditional-uninitialized                                                \
	-Wimplicit-float-conversion                                                \
	-Wimplicit-int-conversion	                                               \
	-Wshorten-64-to-32                                                         \
	-Wstring-concatenation                                                     \
	-Wunused-but-set-parameter                                                 \
	-Wsizeof-array-div                                                         \
	-Wtautological-constant-in-range-compare                                   \
	-Wno-extra-semi-stmt                                                       \
	-Wthread-safety                                                            \
	-Wdangling																   \
	# -Wunsafe-buffer-usage                                                      \

WARNS_GCC := $(WARNS_COMMON)                                                  \
	-Whardened                                                                 \
	-Wshift-overflow                                                           \
	-Wunused-but-set-parameter                                                 \
	-Wstrict-overflow=5                                                        \
	-Wmissing-attributes                                                       \
	-Wmismatched-dealloc                                                       \
	-Wtrivial-auto-var-init                                                    \
	-Wuse-after-free=3                                                         \
	-Wuseless-cast                                                             \
	--strict-flex-arrays=3                                                     \
	-Wsuggest-attribute=pure                                                   \
	-Wsuggest-attribute=const                                                  \
	-Wsuggest-attribute=noreturn                                               \
	-Wsuggest-attribute=malloc                                                 \
	-Wsuggest-attribute=format                                                 \
	-Wsuggest-attribute=cold                                                   \
	-Walloc-size                                                               \
	-Walloca                                                                   \
	-Warith-conversion                                                         \
	-Warray-bounds=2                                                           \
	-Warray-compare                                                            \
	-Warray-parameter                                                          \
	-Wattribute-alias=2                                                        \
	-Wduplicated-branches                                                      \
	-Wduplicated-cond                                                          \
	-Wzero-length-bounds                                                       \
	-Wunsafe-loop-optimizations                                                \
	-Wtype-limits                                                              \
	-Wdangling-pointer                                                         \
	-Wsizeof-pointer-memaccess                                                 \
	-Wpacked                                                                   \
	-Wrestrict                                                                 \
	-Winit-self                                                                \
	-Wlogical-op                                                               \
	-Wstringop-overflow=4                                                      \
	-Wstringop-truncation

CFLAGS_COMMON_OPT := -D_GNU_SOURCE											   \
					 -pipe													   \
					 -ffunction-sections									   \
					 -fdata-sections					   					   \
					 -finline-functions 									   \
					 -fvisibility=hidden									   \
					 -fstack-protector-strong            					   \
					 -fcf-protection=full									   \
					 -ftrivial-auto-var-init=zero 							   \
					 -fno-common              								   \
					 -fstack-clash-protection 								   \
					 -g3													   \
					 -DFT_NTHREADS=$(MAXTHREADS)							   \
					 -DFT_LLC=$(LLC)
 
CFLAGS_OPT   := $(CFLAGS_COMMON_OPT) -march=native -mtune=native -flto -O3 -ffast-math
CFLAGS_NOOPT := $(CFLAGS_COMMON_OPT)
CFLAGS_NOLTO := $(CFLAGS_COMMON_OPT) -march=native -mtune=native -O3 -ffast-math

SANITIZE   := -fsanitize=address,alignment,undefined -fsanitize-recover=null

ifeq ($(findstring clang,$(CC_ID)),clang)
  WARNS  := $(WARNS_CLANG)
  AR     := llvm-ar rcs
  RANLIB := llvm-ranlib
  LDFLAGS_LINK := -fuse-ld=lld
else
  WARNS  := $(WARNS_GCC)
  AR     := gcc-ar rcs
  RANLIB := gcc-ranlib
  LDFLAGS_LINK :=
endif

CFLAGS := $(MARCH) $(CFLAGS_OPT) $(WARNS)

SRCS_ALLOC := \
	src/alloc/ft_alloc_clone.c \
	src/alloc/huge_matcher/ft_huge_matcher.c \
	src/alloc/page_allocator/ft_palloc.c \
	src/alloc/page_allocator/ft_palloc_vtable.c \
	src/alloc/arena/ft_arena_alloc_utils.c \
	src/alloc/arena/ft_arena_alloc_scopes.c \
	src/alloc/arena/ft_arena_alloc.c \
	src/alloc/arena/ft_arena_vtable.c \
	src/alloc/gpa/ft_gpa.c \
	src/alloc/gpa/ft_gpa_alloc.c \
	src/alloc/gpa/ft_gpa_free.c \
	src/alloc/gpa/ft_gpa_realloc.c \
	src/alloc/gpa/ft_gpa_vtable.c \
	src/alloc/report/ft_report.c \
	src/alloc/report/ft_report_alloc.c \
	src/alloc/report/ft_report_free.c \
	src/alloc/report/ft_report_realloc.c \
	src/alloc/report/ft_report_vtable.c

SRCS_CSTR := \
	src/cstr/ft_strlen.c \
	src/cstr/ft_cstr_to_str.c

SRCS_CTYPE := \
	src/ctype/asm/ft_isalnum.c \
	src/ctype/asm/ft_isalpha.c \
	src/ctype/asm/ft_isascii.c \
	src/ctype/asm/ft_isdigit.c \
	src/ctype/asm/ft_isprint.c \
	src/ctype/asm/ft_isxdigit.c \
	src/ctype/asm/ft_isspace.c \
	src/ctype/ft_isascii.c \
	src/ctype/ft_isalnum.c \
	src/ctype/ft_isprint.c \
	src/ctype/ft_isxdigit.c \
	src/ctype/ft_isspace.c \
	src/ctype/ft_isalpha.c \
	src/ctype/ft_isdigit.c

SRCS_SYSCALLS := \
	src/syscalls/ft_read.c \
	src/syscalls/ft_write.c \
	src/syscalls/ft_fmap.c \
	src/syscalls/ft_mremap.c \
	src/syscalls/ft_lockf.c \
	src/syscalls/ft_mmap.c \
	src/syscalls/ft_stat.c

SRCS_IO := \
	src/io/ft_printf_helpers2.c \
	src/io/ft_read_file_portable.c \
	src/io/ft_read_file.c \
	src/io/ft_printf_helpers.c \
	src/io/ft_printf.c \
	src/io/ft_lockf.c

SRCS_MATH := \
	src/math/3d/ft_3dadd.c \
	src/math/3d/ft_3dsub.c \
	src/math/3d/ft_3dnorm.c \
	src/math/3d/ft_3dunit.c \
	src/math/3d/ft_3dmul.c \
	src/math/3d/ft_3ddiv.c \
	src/math/3d/ft_3ddot.c \
	src/math/3d/ft_3dcross.c \
	src/math/ft_pow.c \
	src/math/ft_round.c \
	src/math/ft_fabs.c \
	src/math/ft_sqrt.c \
	src/math/ft_pow_signed.c \
	src/math/ft_q_sqrt.c \
	src/math/ft_rsqrt.c \
	src/math/ft_drsqrt_xn.c \
	src/math/ft_sqrt_xn.c

SRCS_MEM := \
	src/mem/ft_membroadcast.c \
	src/mem/ft_memtake.c \
	src/mem/arch/ft_memcpy.c \
	src/mem/arch/ft_memset.c \
	src/mem/arch/ft_memchr.c \
	src/mem/arch/ft_memcmp.c \
	src/mem/arch/ft_memmove.c \
	src/mem/ft_bzero.c \
	src/mem/portable/ft_memcpy.c \
	src/mem/portable/ft_memset.c \
	src/mem/vec128/ft_memcpy.c \
	src/mem/vec128/ft_memset.c \
	src/mem/vec128/ft_memcmp.c \
	src/mem/vec128/ft_memchr.c \
	src/mem/ft_prefetch_noop.c \
	src/mem/vec512/ft_memcpy_vec512.c \
	src/mem/vec512/ft_memset_vec512.c \
	src/mem/vec512/ft_memcmp_vec512.c \
	src/mem/vec512/ft_memchr_vec512.c \
	src/mem/ft_overlap.c \
	src/mem/ft_fatptr.c \
	src/mem/ft_movs.c \
	src/mem/ft_align.c \
	src/mem/vec256/ft_memcpy_vec256.c \
	src/mem/vec256/ft_memset_vec256.c \
	src/mem/vec256/ft_memcmp_vec256.c \
	src/mem/vec256/ft_memchr_vec256.c \
	src/mem/hugebranches/ft_memcpy_huge.c \
	src/mem/hugebranches/ft_memmove_huge.c \
	src/mem/hugebranches/ft_memset_huge.c \
	src/mem/streaming/ft_memcpy_streaming.c \
	src/mem/streaming/ft_memset_streaming.c \
	src/mem/ft_prefetch_intrin.c \
	src/mem/ft_memfence.c

SRCS_THREADPOOL := \
	src/threadpool/ft_threadpool.c \
	src/threadpool/ft_threadpool_wait.c

SRCS_VEC := \
	src/containers/vec/ft_vec_remove.c \
	src/containers/vec/ft_vec_pop.c \
	src/containers/vec/ft_vec.c \
	src/containers/vec/ft_vec_free.c \
	src/containers/vec/ft_vec_push_back.c \
	src/containers/vec/ft_vec_get.c \
	src/containers/vec/ft_vec_bytesize.c \
	src/containers/vec/ft_vec_extend.c \

SRCS_STR := \
	src/containers/str/ft_str.c \
	src/containers/str/ft_str_extend.c \
	src/containers/str/ft_str_push_back.c \
	src/containers/str/ft_str_remove.c

SRCS_BMI := \
	src/bmi/__populate.c \
	src/bmi/ft_bswap.c \
	src/bmi/ft_rotl.c \
	src/bmi/asm/ft_bswap_asm.c \
	src/bmi/asm/ft_memctz_asm.c \
	src/bmi/asm/ft_memclz_asm.c \
	src/bmi/asm/ft_get128.c \
	src/bmi/asm/ft_get256.c \
	src/bmi/asm/ft_get512.c \
	src/bmi/asm/ft_bitpack.c \
	src/bmi/asm/ft_bitpack_intrin.c \
	src/bmi/ft_to_be_from_be.c \
	src/bmi/ft_to_be_from_le.c \
	src/bmi/ft_rollmask.c \
	src/bmi/ft_memctz.c \
	src/bmi/ft_memclz.c \
	src/bmi/ft_tern.c \
	src/bmi/__maxs.c \
	src/bmi/__max.c \
	src/bmi/__hasz.c \
	src/bmi/ft_next_pow2.c

SRCS_HASH := \
	src/hash/murmur3/ft_murmur3.c \
	src/hash/murmur3/ft_murmur_helpers.c \
	src/hash/xxh3/ft_xxh3_medium_sizes.c \
	src/hash/xxh3/ft_xxh3_large_sizes.c \
	src/hash/xxh3/ft_xxh3_secret.c \
	src/hash/xxh3/ft_xxh3.c \
	src/hash/xxh3/ft_xxh3_small_sizes.c \
	src/hash/xxh3/ft_xxh3_finalizers.c \
	src/hash/xxh3/ft_xxh3_mul128_fold64.c \
	src/hash/xxh3/ft_xxh3_avalanche.c \
	src/hash/xxh3/ft_xxh3_xorshift.c \
	src/hash/xxh3/ft_xxh3_rrmxmx.c

SRCS_ENV := \
	src/env/ft_getenv.c

SRCS_MAP := \
	src/containers/swissmap/ft_map_insert.c \
	src/containers/swissmap/ft_map_lookup.c \
	src/containers/swissmap/ft_map_delete.c \
	src/containers/swissmap/ft_map_rehash.c \
	src/containers/swissmap/ft_map_insert_unchecked.c \
	src/containers/swissmap/ft_map.c

SRCS_HINT := \
	src/hint/ft_pin_invariant.c \
	src/hint/ft_assume.c \
	src/hint/ft_hardcrash.c

SRCS_TOK := \
	src/containers/tokenizer/ft_eat_u128.c \
	src/containers/tokenizer/ft_eat_u256.c \
	src/containers/tokenizer/ft_eat_u512.c \
	src/containers/tokenizer/ft_eat_until.c \
	src/containers/tokenizer/ft_eat_u8.c \
	src/containers/tokenizer/ft_sets.c \
	src/containers/tokenizer/ft_tokenizer.c \
	src/containers/tokenizer/ft_eat_while.c

SRCS_TIME := \
	src/time/ft_get_nanos.c

SRCS_RNG := \
	src/rng/ft_xoshiro256ss.c

SRCS_PERF := \
	src/perf/ft_perf_create_counters.c \
	src/perf/ft_bind_process_to_cpu.c \
	src/perf/ft_get_flag_groups.c \
	src/perf/ft_perf_counter_interface.c \
	src/perf/ft_perf_destroy_counters.c \
	src/perf/ft_perf_sampling.c

SRCS_SORT := \
	src/sort/ft_qsort.c \
	src/sort/ft_qsort_u64s.c

SRCS_TAILOR := \
	src/tailor/ft_tailor_resample.c \
	src/tailor/ft_tailor_fuzz.c \
	src/tailor/ft_tailor_get_rand_buffer.c \
	src/tailor/ft_tailor_get_random_num.c \
	src/tailor/ft_tailor_new.c \
	src/tailor/ft_tailor_calibration.c \
	src/tailor/ft_tailor_summary.c \
	src/tailor/ft_tailor_bytes.c \
	src/tailor/ft_tailor_run.c \
	src/tailor/ft_tailor_getcount.c \
	src/tailor/ft_tailor_top.c

SRCS_FUZZ := \
	src/fuzzer/ft_fuzzer_get_rand.c \
	src/fuzzer/ft_fuzzer_initrand.c \
	src/fuzzer/ft_fuzzer.c

MODULES := SYSCALLS ALLOC CSTR CTYPE IO MATH MEM 		\
		   HASH VEC STR BMI ENV MAP HINT TOK THREADPOOL	\
		   TIME PERF RNG TAILOR SORT FUZZ

SRCS := $(foreach m,$(MODULES),$(SRCS_$(m)))
OBJS := $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))


all: $(NAME)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $@ $^
	@$(RANLIB) $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

analyze:
	$(SCANNER) $(CC_CLANG) $(WARNS_CLANG) $(CFLAGS_OPT) $(MARCH) $(INCLUDES) \
		-Xclang -analyzer-output=text --analyze $(SRCS)
	$(SCANNER) $(CC_CLANG) $(WARNS_CLANG) $(CFLAGS_OPT) $(INCLUDES) \
		-Xclang -analyzer-output=text --analyze $(SRCS)
	$(CC_GCC) $(WARNS_GCC) $(CFLAGS_OPT) $(MARCH) $(INCLUDES) \
		-fanalyzer $(SRCS) -c && rm -f *.o
	$(CC_GCC) $(WARNS_GCC) $(CFLAGS_OPT) $(INCLUDES) \
		-fanalyzer $(SRCS) -c && rm -f *.o
	norminette

.PHONY: all clean fclean re analyze
