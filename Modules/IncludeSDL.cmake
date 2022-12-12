# Program:   myAppSLD
# Module:    IncludeSDL.cmake
# Language:  CMake 3.0
# Date:      $Date: 2022-10-30
#
# Description:
# CMake Project file for myAppSDL

MESSAGE(" Include Libs")

# Set Libraries Dir
SET(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Libs")

SET(SDL2_DIR "${INCLUDE_DIR}/SDL2")
SET(SDL2_INCLUDE_DIR ${SDL2_DIR}/include)

SET(SDL2_IMAGE_DIR "${INCLUDE_DIR}/SDL2_IMAGE")
SET(SDL2_IMAGE_INCLUDE_DIR ${SDL2_IMAGE_DIR}/include)

SET(SDL2_TTF_DIR "${INCLUDE_DIR}/SDL2_TTF")
SET(SDL2_TTF_INCLUDE_DIR ${SDL2_TTF_DIR}/include)

SET(SDL2_MIXER_DIR "${INCLUDE_DIR}/SDL2_MIXER")
SET(SDL2_MIXER_INCLUDE_DIR ${SDL2_MIXER_DIR}/include)

# Support both 32 and 64 bit builds
IF (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	SET(SDL2_LIBRARY ${SDL2_DIR}/lib/x64)
	SET(SDL2_IMAGE_LIBRARY ${SDL2_IMAGE_DIR}/lib/x64)
	SET(SDL2_TTF_LIBRARY ${SDL2_TTF_DIR}/lib/x64)
	SET(SDL2_MIXER_LIBRARY ${SDL2_MIXER_DIR}/lib/x64)
ELSE ()
	SET(SDL2_LIBRARY ${SDL2_DIR}/lib/x86)
	SET(SDL2_IMAGE_LIBRARY ${SDL2_IMAGE_DIR}/lib/x86)
	SET(SDL2_TTF_LIBRARY ${SDL2_TTF_DIR}/lib/x86)
	SET(SDL2_MIXER_LIBRARY ${SDL2_MIXER_DIR}/lib/x86)
ENDIF ()

SET(SDL2_LIBRARIES "${SDL2_LIBRARY}/SDL2main.lib;${SDL2_LIBRARY}/SDL2.lib")
SET(SDL2_IMAGE_LIBRARIES "${SDL2_IMAGE_LIBRARY}/SDL2_image.lib")
SET(SDL2_TTF_LIBRARIES "${SDL2_TTF_LIBRARY}/SDL2_ttf.lib")
SET(SDL2_MIXER_LIBRARIES "${SDL2_MIXER_LIBRARY}/SDL2_mixer.lib")

SET(SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
SET(SDL2_LIBRARIES ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

# Include Libs
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARIES})