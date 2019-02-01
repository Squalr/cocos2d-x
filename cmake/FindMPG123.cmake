# libmpg123 finder module
include(FindPackageHandleStandardArgs)

# manual finds
if(NOT MPG123_INCLUDE_DIR)
    find_path(MPG123_INCLUDE_DIR mpg123.h)
endif()

if(NOT MPG123_LIBRARY)
    find_library(MPG123_LIBRARY libmpg123)
endif()

find_package_handle_standard_args(MPG123 REQUIRED_VARS
    MPG123_INCLUDE_DIR
    MPG123_LIBRARY
)

if(NOT TARGET MPG123::MPG123)
    add_library(MPG123::MPG123 UNKNOWN IMPORTED)
    set_target_properties(MPG123::MPG123 PROPERTIES
        IMPORTED_LOCATION ${MPG123_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${MPG123_INCLUDE_DIR}
    )
endif()
