#!/usr/bin/env bash
set -e

if [ ! -d "build" ]; then
  echo "Build directory does not exist, creating..."
  mkdir -p build
  cd build
  cmake ..
else
  echo "Build directory exists, rebuilding..."
  cd build
fi

cmake --build .
