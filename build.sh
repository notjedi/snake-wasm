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

cmake $CMAKE_FLAGS -B build && cmake --build build
