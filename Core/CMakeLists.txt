# Program:   myAppSLD
# Module:    CMakeLists.txt
# Language:  CMake 3.0
# Date:      $Date: 2022-10-30
#
# Description:
# CMake Project file for myAppSDL

PROJECT (Core)

MESSAGE(" Configure: ${PROJECT_NAME}")

SET(CORE_PROJECT_SRCS 
  Core.cpp Core.h
  Game.cpp Game.h
  GameState.h
  GameSettings.cpp GameSettings.h
  Timer.cpp Timer.h
  GameEngine.cpp GameEngine.h
  AssetManager.cpp AssetManager.h
  AudioManager.cpp AudioManager.h
  GraphicManager.cpp GraphicManager.h
  InputManager.cpp InputManager.h  
  Vector2D.cpp Vector2D.h 
  Math3D.h
  GameEntity.cpp GameEntity.h
)

add_library(Core STATIC ${CORE_PROJECT_SRCS})

target_include_directories(Core PUBLIC .)

# Copy dll files to Binary Dir
file(COPY ${SDL2_LIBRARY}/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_IMAGE_LIBRARY}/SDL2_image.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})		
file(COPY ${SDL2_IMAGE_LIBRARY}/zlib1.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_IMAGE_LIBRARY}/libpng16-16.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_TTF_LIBRARY}/SDL2_ttf.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_TTF_LIBRARY}/libfreetype-6.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_MIXER_LIBRARY}/SDL2_mixer.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
