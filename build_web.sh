#!/bin/bash

cmake -DCMAKE_TOOLCHAIN_FILE=/usr/lib/emscripten/cmake/Modules/Platform/Emscripten.cmake -DPLATFORM_WEB=ON -B build &&
	cmake --build build
