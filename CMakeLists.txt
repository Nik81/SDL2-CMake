# Program:   myAppSLD
# Module:    CMakeLists.txt
# Language:  CMake 3.0
# Date:      $Date: 2022-10-30
#
# Description:
# CMake Project file for myAppSDL

CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

PROJECT(myApp VERSION "1.0.0")

MESSAGE("CONFIGURE: ${PROJECT_NAME}")

# Create the header to configure the classes
CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/appDefines.h.in ${PROJECT_BINARY_DIR}/appDefines.h @ONLY)

INCLUDE (${PROJECT_SOURCE_DIR}/Modules/IncludeSDL.cmake)

INCLUDE_DIRECTORIES(${PRJ_SOURCE_DIR}/Core) 
INCLUDE_DIRECTORIES(${PRJ_SOURCE_DIR}/App)
SUBDIRS (Core)
SUBDIRS (App)

OPTION(BUILD_TESTING "Build the testing tree." OFF)

IF(BUILD_TESTING)
  INCLUDE_DIRECTORIES(${PRJ_SOURCE_DIR}/Testing)
  SUBDIRS (Testing)
ENDIF(BUILD_TESTING)

# Enable Edit and Continue
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_CXX_FLAGS_DEBUG "/ZI")
  set(CMAKE_SHARED_LINKER_FLAGS "/SAFESEH:NO")
  set(CMAKE_EXE_LINKER_FLAGS "/SAFESEH:NO")
endif()

#file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})
