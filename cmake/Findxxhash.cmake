include(SelectLibraryConfigurations)
include(FindPackageHandleStandardArgs)

if(NOT XXHASH_INCLUDE_DIR)
    FIND_PATH(XXHASH_INCLUDE_DIR NAMES xxhash.h)
endif()

if(NOT XXHASH_LIBRARY)
    find_library(XXHASH_LIBRARY_RELEASE NAMES xxhash )
    find_library(XXHASH_LIBRARY_DEBUG NAMES debug/lib/xxhash )
    select_library_configurations(XXHASH)
endif()

set(XXHASH_LIBRARIES ${XXHASH_LIBRARY})
set(XXHASH_INCLUDE_DIRS ${XXHASH_INCLUDE_DIR})

find_package_handle_standard_args(XXHASH REQUIRED_VARS XXHASH_LIBRARY XXHASH_INCLUDE_DIR)

add_library(xxhash::xxhash UNKNOWN IMPORTED)
set_target_properties(xxhash::xxhash PROPERTIES
    IMPORTED_LOCATION ${XXHASH_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${XXHASH_INCLUDE_DIR}
)


