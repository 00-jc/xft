xft_add_harness(
  gentable
  LIB xft
  SOURCES
    src/xft_gentable_main.c
    src/xft_gentable_iterate.c
    src/xft_gentable_classify.c
    src/xft_gentable_intern.c
    src/xft_gentable_jmpline.c
    src/xft_gentable_tag.c
    src/xft_gentable_emit.c
  INCLUDES include
)

# regenerates src/xid/xft_xidtable.c from DerivedCoreProperties.txt in the
# source root; gentable opens its output without O_CREAT, so touch it first
if(XFT_BOOTSTRAP_XID)
  add_custom_target(
    xid-table ALL
    COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_SOURCE_DIR}/src/xid/xft_xidtable.c
    COMMAND gentable ${PROJECT_SOURCE_DIR}/DerivedCoreProperties.txt
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    DEPENDS gentable
    COMMENT "gentable: generating src/xid/xft_xidtable.c"
    VERBATIM
  )
endif()
