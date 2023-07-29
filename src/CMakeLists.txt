set(HEADER_LIST "${dict_SOURCE_DIR}/include/dict_lib/dict.h")
add_library(dict_library SHARED dict_lib.c)
target_include_directories(dict_library PUBLIC ../include)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)