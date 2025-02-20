cmake_minimum_required( VERSION 3.5 )

project( MLR VERSION 0.1 LANGUAGES CXX )
set(PROJECT_DESCRIPTION "MLR C++ math library")

include(GNUInstallDirs)

if( NOT CMAKE_BUILD_TYPE )
        set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
endif()
set( CMAKE_CXX_STANDARD 26 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
add_compile_options(-march=native -O3 -mfpmath=sse -g)
add_compile_options(-D_FILE_OFFSET_BITS=64)
add_compile_options(-fdata-sections)
add_compile_options(-fpermissive)
add_compile_options(-ffunction-sections)
add_compile_options(-Wno-array-bounds)
add_compile_options(-Wno-unused-parameter)
add_compile_options(-Wno-pedantic)
add_compile_options(-Wno-narrowing)
add_link_options(-Wl,--gc-sections)
add_link_options(-Wl,--print-gc-sections)
add_link_options(-Wl,-s)

find_package(OpenGL)
if(OpenGL_Found)
add_compile_options(-DHAVE_GLCOREARB_H=1)
endif()

add_library( mlr INTERFACE )
target_include_directories( mlr INTERFACE
        PUBLIC_HEADER $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/mlr DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT headers)

add_executable( example examples/example.cpp )
target_link_libraries( example mlr )

