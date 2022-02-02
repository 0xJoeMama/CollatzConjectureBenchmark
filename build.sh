#!/usr/bin/env sh

set -e

if [ "$1" = "clean" ]; then
    rm -rf "$PWD/build/"
fi

mkdir -p "$PWD/build/"
cmake -B "$PWD/build"
make -C "$PWD/build"

mv "$PWD/build/collatz-benchmark" "$PWD"

