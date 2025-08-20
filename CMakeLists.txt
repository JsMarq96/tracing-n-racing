cmake_minimum_required(VERSION 3.21)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

target_link_libraries(tracing_n_racing glm)
