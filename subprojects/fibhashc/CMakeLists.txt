xft_add_harness(
  fibhashc
  LIB xft
  SOURCES
    src/entry_point.c
    src/pipeline.c
    src/load.c
	src/calc_hash.c
  INCLUDES include
)
