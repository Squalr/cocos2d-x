include(SelectLibraryConfigurations)
include(FindPackageHandleStandardArgs)

if(NOT AUDIOTOOLBOX_LIBRARY)
    find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
endif()

find_package_handle_standard_args(AudioToolbox REQUIRED_VARS AUDIOTOOLBOX_LIBRARY)

add_library(AudioToolbox::AudioToolbox INTERFACE IMPORTED)
set_target_properties(AudioToolbox::AudioToolbox PROPERTIES
    INTERFACE_LINK_LIBRARIES ${AUDIOTOOLBOX_LIBRARY}
)


