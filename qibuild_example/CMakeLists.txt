cmake_minimum_required(VERSION 2.8)

# Give a name to the project.
project(image_module)

# You need this to find the qiBuild CMake framework
find_package(qibuild)

# Create a list of source files
set(_srcs
    optimizedimage.cpp
    optimizedimage.hpp
    main.cpp)

if(OPTIMIZEDIMAGE_IS_REMOTE)
    add_definitions( " -DOPTIMIZEDIMAGE_IS_REMOTE ")
    qi_create_bin(optimized_image ${_srcs})
else()
    # Create a plugin, that is a shared library, and make
    # sure it is built in lib/naoqi
    qi_create_lib(image_module SHARED ${_srcs} SUBFOLDER naoqi)
endif()

qi_use_lib(image_module ALCOMMON BOOST ALVISION OPENCV2_CORE OPENCV2_HIGHGUI)
