# libvorbis finder module
include(FindPackageHandleStandardArgs)
find_package(Ogg REQUIRED)

if (NOT VORBIS_INCLUDE_DIR)
    find_path(VORBIS_INCLUDE_DIR vorbis/codec.h)
endif()

if (NOT VORBIS_LIBRARY)
    find_library(VORBIS_LIBRARY vorbis)
endif()

if (NOT VORBISENC_LIBRARY)
    find_library(VORBISENC_LIBRARY vorbisenc)
endif()

if(NOT VORBISFILE_LIBRARY)
    find_library(VORBISFILE_LIBRARY vorbisfile)
endif()

find_package_handle_standard_args(Vorbis REQUIRED_VARS
    VORBIS_INCLUDE_DIR
    VORBIS_LIBRARY
    VORBISENC_LIBRARY
    VORBISFILE_LIBRARY
)

if (NOT TARGET Vorbis::Codec)
    add_library(Vorbis::Codec UNKNOWN IMPORTED)
    set_target_properties(Vorbis::Codec PROPERTIES
        IMPORTED_LOCATION ${VORBIS_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${VORBIS_INCLUDE_DIR}
    )
    target_link_libraries(Vorbis::Codec INTERFACE Ogg::Ogg)
endif()

if (NOT TARGET Vorbis::Encoder)
    add_library(Vorbis::Encoder UNKNOWN IMPORTED)
    set_target_properties(Vorbis::Encoder PROPERTIES
        IMPORTED_LOCATION ${VORBISENC_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${VORBIS_INCLUDE_DIR}
    )
    target_link_libraries(Vorbis::Encoder INTERFACE Vorbis::Codec)
endif()

if(NOT TARGET Vorbis::File)
    add_library(Vorbis::File UNKNOWN IMPORTED)
    set_target_properties(Vorbis::File PROPERTIES
        IMPORTED_LOCATION ${VORBISFILE_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${VORBIS_INCLUDE_DIR}
    )
    target_link_libraries(Vorbis::File INTERFACE Vorbis::Codec)
endif()
