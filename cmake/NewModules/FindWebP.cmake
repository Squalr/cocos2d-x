include(SelectLibraryConfigurations)
include(FindPackageHandleStandardArgs)

if(NOT WEBP_INCLUDE_DIR)
    find_path(WEBP_INCLUDE_DIR NAMES webp/decode.h)
endif()

if(NOT WEBP_LIBRARY)
    find_library(WEBP_LIBRARY_RELEASE NAMES webp)
    find_library(WEBP_LIBRARY_DEBUG NAMES webpd)
    select_library_configurations(WEBP)
endif()

set(WEBP_LIBRARIES ${WEBP_LIBRARY})
set(WEBP_INCLUDE_DIRS ${WEBP_INCLUDE_DIR})

find_package_handle_standard_args(WEBP REQUIRED_VARS WEBP_LIBRARY WEBP_INCLUDE_DIR)

add_library(WebP::WebP UNKNOWN IMPORTED)
set_target_properties(WebP::WebP PROPERTIES
    IMPORTED_LOCATION "${WEBP_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES ${WEBP_INCLUDE_DIR}
)


