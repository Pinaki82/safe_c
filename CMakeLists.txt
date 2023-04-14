# mkdir build
# cd build
# cmake -G "MinGW Makefiles" ..
# or,
# cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..
# make -j4
# or,
# mingw32-make -j4

cmake_minimum_required(VERSION 3.0)
project(safe_c)


# https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake
include_directories(include)

add_executable(safe_c
  src/main.c
  include/sf_c.h
 )


# Add compiler flags for GCC and Clang
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(safe_c PRIVATE -Wall -Wextra -isystem safeclib/safe_lib.h)
endif()

# Add compiler flags for MSVC
if(MSVC)
  target_compile_options(safe_c PRIVATE /W4)
endif()

# Set linker flags for all builds
if(WIN32)
  # For Windows systems (MinGW-w64 or MSVC)
  target_link_options(safe_c PRIVATE -static-libgcc -static-libstdc++ -lsafec)
  if(MSVC)
    # For MSVC on Windows
    target_compile_options(safe_c PRIVATE /W4 /WX)
  endif()
else()
  # For non-Windows systems (GCC or Clang)
  target_link_options(safe_c PRIVATE -static -lsafec)
  # target_compile_options(safe_c PRIVATE -Werror)
endif()

# Set build type to Release by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Set compiler and linker flags for Debug and Release builds
target_compile_options(safe_c PRIVATE
  $<$<CONFIG:Debug>:-O0 -g>
  $<$<CONFIG:Release>:-O2>
)

if(WIN32 AND MSVC)
  target_link_options(safe_c PRIVATE
    $<$<CONFIG:Debug>:/DEBUG:FULL>
    $<$<CONFIG:Release>:/DEBUG:NONE>
  )
else()
  target_link_options(safe_c PRIVATE
    # $<$<CONFIG:Debug>:-Wl,--export-all-symbols>
  )
endif()

