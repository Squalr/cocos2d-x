#.rst:
# FindSteam
# ------------
#
# Locate STEAM library
#
# This module defines
#
# ::
#
#   STEAM_LIBRARIES, the library to link against
#   STEAM_FOUND, the libraries needed to use STEAM
#   STEAM_INCLUDE_DIRS, where to find headers.
#

find_path(STEAM_INCLUDE_DIR
	NAMES STEAM/steam_api.h
	PATH_SUFFIXES include
)

find_library(STEAM_LIBRARY 
	NAMES STEAM
	PATH_SUFFIXES lib
)

set(STEAM_INCLUDE_DIRS "${STEAM_INCLUDE_DIR}")
set(STEAM_LIBRARIES "${STEAM_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(STEAM DEFAULT_MSG STEAM_LIBRARIES STEAM_INCLUDE_DIRS)

mark_as_advanced(STEAM_INCLUDE_DIR STEAM_LIBRARY)
