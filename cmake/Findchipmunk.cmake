# libogg finder module
include(FindPackageHandleStandardArgs)

if(NOT CHIPMUNK_INCLUDE_DIR)
    find_path(CHIPMUNK_INCLUDE_DIR chipmunk/chipmunk.h)
endif()

if(NOT CHIPMUNK_LIBRARY)
    find_library(CHIPMUNK_LIBRARY chipmunk)
endif()

find_package_handle_standard_args(chipmunk REQUIRED_VARS
    CHIPMUNK_INCLUDE_DIR
    CHIPMUNK_LIBRARY
)

if(NOT TARGET chipmunk::chipmunk)
    add_library(chipmunk::chipmunk UNKNOWN IMPORTED)
    set_target_properties(chipmunk::chipmunk PROPERTIES
        IMPORTED_LOCATION ${CHIPMUNK_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${CHIPMUNK_INCLUDE_DIR}
    )
endif()