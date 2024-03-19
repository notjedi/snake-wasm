#!/bin/bash

CMAKE_FLAGS=""
while [[ $# -gt 0 ]]; do
	key="$1"

	case $key in
	--release)
		CMAKE_FLAGS="-DCMAKE_BUILD_TYPE=Release"
		shift
		;;
	*)
		echo "Usage: $0 [--release]" >&2
		exit 1
		;;
	esac
done

cmake -DCMAKE_TOOLCHAIN_FILE=/usr/lib/emscripten/cmake/Modules/Platform/Emscripten.cmake -DPLATFORM_WEB=ON $CMAKE_FLAGS -B build &&
	cmake --build build
