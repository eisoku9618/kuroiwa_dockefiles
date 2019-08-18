cmake_minimum_required(VERSION 2.8)
project(ode_tutorial)

find_package(PkgConfig)
pkg_search_module(ODE REQUIRED ode)

find_package(OpenGL REQUIRED)
find_package(X11)

include_directories(${ODE_INCLUDE_DIRS})
link_directories(${ODE_LIBRARY_DIRS})

add_executable(2dof_arm 2dof_arm.cpp)
target_link_libraries(2dof_arm ${ODE_LIBRARIES} drawstuff ${OPENGL_LIBRARY} pthread ${X11_LIBRARIES})
