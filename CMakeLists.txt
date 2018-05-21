cmake_minimum_required(VERSION 2.8)
project(nao_vision_example)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake")

add_executable(NAO_app main.cpp
                       src/detect_faces.cpp
                       src/common.cpp
                       src/move_head.cpp
                       src/state.cpp
                       src/action.cpp
                       src/event_timer.cpp
                       src/configuration.cpp
                       src/nao_talk.cpp
                       src/game.cpp
                       src/nao_walk.cpp
                       src/event.cpp
                       src/nao_broker.cpp
              )
#Adding Libraries
target_link_libraries(NAO_app ${NOOS_LIBRARY}
                              ${NAO_LIBRARIES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}-static-libstdc++ -static-libgcc")
set(CMAKE_CXX_FLAGS "-std=gnu++1y -march=atom -mtune=atom -mfpmath=sse")
