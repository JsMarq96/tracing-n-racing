cmake_minimum_required(VERSION 3.21)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")

set(CMAKE_BUILD_TYPE Debug)

project(tracing_n_racing)

file(GLOB H_SOURCES "src/*.h")
file(GLOB CPP_SOURCES "src/*.cpp")
file(GLOB C_SOURCES "src/*.c")
file(GLOB SUBFOLDER_H_SOURCES "src/*/*.h")
file(GLOB SUBFOLDER_CPP_SOURCES "src/*/*.cpp")
file(GLOB SUBFOLDER_C_SOURCES "src/*/*.c")

add_executable(tracing_n_racing ${C_SOURCES} ${CPP_SOURCES} ${H_SOURCES} ${SUBFOLDER_H_SOURCES} ${SUBFOLDER_C_SOURCES} ${SUBFOLDER_CPP_SOURCES})

target_compile_options(tracing_n_racing PRIVATE -pthread)
set_target_properties(tracing_n_racing PROPERTIES OUTPUT_NAME "t_n_r")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tracing_n_racing)
set_property(TARGET tracing_n_racing PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(libraries/glm)
target_link_libraries(tracing_n_racing glm)

include_directories(${C_SOURCES} ${CPP_SOURCES} ${H_SOURCES} ${SUBFOLDER_H_SOURCES} ${SUBFOLDER_C_SOURCES} ${SUBFOLDER_CPP_SOURCES})