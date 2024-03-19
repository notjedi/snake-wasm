cmake_minimum_required(VERSION 3.10)
project(snake-wasm C)

set(SOURCES
    src/main.c
)

# set(HEADERS
#     include/my_header.h
# )

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

if (PLATFORM_WEB)
    # https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)
    add_compile_definitions(PLATFORM_WEB)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s GL_ENABLE_GET_PROC_ADDRESS=1")
    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s GL_ENABLE_GET_PROC_ADDRESS=1 --shell-file ${CMAKE_SOURCE_DIR}/include/wasm/raylib/minshell.html")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    include_directories(include/wasm)
    add_library(raylib STATIC IMPORTED)
    set_target_properties(raylib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/wasm/raylib/libraylib.a)

    add_executable(snake_wasm ${SOURCES} ${HEADERS})
    target_link_libraries(snake_wasm raylib)
    target_link_libraries(snake_wasm m)
else()
    include_directories(include/x86)
    link_directories(lib/x86)
    link_libraries(raylib)

    add_executable(snake_wasm ${SOURCES} ${HEADERS})
    target_link_libraries(snake_wasm m)

    # Optionally, configure installation
    # install(TARGETS my_project DESTINATION bin)
    # install(FILES ${HEADERS} DESTINATION include)
endif()
