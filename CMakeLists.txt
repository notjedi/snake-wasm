cmake_minimum_required(VERSION 3.10)
project(snake-wasm C)

set(SOURCES
    src/main.c
)

# set(HEADERS
#     include/my_header.h
# )

include_directories(include)

# Optionally, you can link libraries if needed
# target_link_libraries(my_project my_library)

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/raylib/libraylib.a)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

add_executable(snake_wasm ${SOURCES} ${HEADERS})
target_link_libraries(snake_wasm raylib)
target_link_libraries(snake_wasm m)

# Optionally, configure installation
# install(TARGETS my_project DESTINATION bin)
# install(FILES ${HEADERS} DESTINATION include)
