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
# source root
if(XFT_BOOTSTRAP_XID)
  add_custom_target(
    xid-table ALL
    COMMAND gentable ${PROJECT_SOURCE_DIR}/DerivedCoreProperties.txt
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    DEPENDS gentable
    COMMENT "gentable: generating src/xid/xft_xidtable.c"
    VERBATIM
  )
endif()
