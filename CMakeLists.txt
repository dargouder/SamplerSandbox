# =============== Initial CMake settings ===============
cmake_minimum_required(VERSION 3.5.0)

project(SamplerSandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include(CTest)

set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
include(DownloadProject.cmake)

# =============== Pybind 11 import set up ===============
download_project(PROJ                pybind11
				 GIT_REPOSITORY      https://github.com/pybind/pybind11.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent Pybind 11 from overriding our compiler/linker options
# when building with Visual Studio

add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})

MESSAGE("PYBIND11 ${pybind11_SOURCE_DIR}")

# =============== Building Libraries ===============
# The Core library is the self-authored core code of the renderer
set(core_libs core)
# The Util library is a composition of 3rd party libraries used for 
# various tasks, such as geometric classes, model import, image output
set(util_libs utils)
include_directories(source/core)
include_directories(source/random)
include_directories(source/utils)
include_directories(source/pycore)

file(GLOB_RECURSE Core_SOURCES "source/core/*.cpp")

add_library(core STATIC ${Core_SOURCES})
add_library(utils STATIC source/utils/lodepng/lodepng.cpp)

# =============== Add executables and link libraries ===============

add_executable(app source/app/main.cpp)
target_link_libraries(app ${core_libs} ${util_libs})


pybind11_add_module(PySampler source/pycore/PyGeometry.cpp)

target_link_libraries(${core_libs} ${util_libs} ${PySampler})

# Executables are:
# solstice : the renderer itself
# solstice_unit_test : the renderer test suite

set(executables app)
#set(CMAKE_CXX_FLAGS_DEBUG  -Weverything)
install(TARGETS ${executables} DESTINATION bin/)