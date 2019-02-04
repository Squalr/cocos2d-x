# libogg finder module
include(FindPackageHandleStandardArgs)

if(NOT OGG_INCLUDE_DIR)
    find_path(OGG_INCLUDE_DIR ogg/ogg.h)
endif()

if(NOT OGG_LIBRARY)
    find_library(OGG_LIBRARY ogg)
endif()

find_package_handle_standard_args(Ogg REQUIRED_VARS
    OGG_INCLUDE_DIR
    OGG_LIBRARY
)

if(NOT TARGET Ogg::Ogg)
    add_library(Ogg::Ogg UNKNOWN IMPORTED)
    set_target_properties(Ogg::Ogg PROPERTIES
        IMPORTED_LOCATION ${OGG_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${OGG_INCLUDE_DIR}
    )
endif()