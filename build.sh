#!/usr/bin/env sh

set -xe

mkdir -p "$PWD/build/"
cmake -B "$PWD/build"
make -C "$PWD/build"

mv "$PWD/build/collatz-benchmark" "$PWD"

