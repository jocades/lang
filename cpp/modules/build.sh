#!/usr/bin/env sh

cxx=/opt/homebrew/opt/llvm/bin/clang++
$cxx -std=c++20 math.cppm --precompile -o math.pcm && $cxx -std=c++20 main.cpp -fprebuilt-module-path=. math.pcm -o main
