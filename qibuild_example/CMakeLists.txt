cmake_minimum_required(VERSION 2.8)
project(nao_vision_example)

find_package(qibuild)

find_package(noos)
message(STATUS "libraries: ${NOOS_LIBRARIES}")
message(STATUS "headers: ${NOOS_INCLUDE_DIRS}")

set(CMAKE_CXX_FLAGS "-std=gnu++1y -static-libstdc++ -march=atom -mtune=atom -mfpmath=sse")
qi_create_bin(nao_vision_example "main.cpp")
qi_use_lib(nao_vision_example ALCOMMON ALPROXIES noos openssl) #ALVISION OPENCV2_CORE OPENCV2_HIGHGUI)
