#!/usr/bin/env bash
set -e

if [ -d "build" ]; then
  echo "Removing existing build directory..."
  rm -rf build AppMine ModelMine AppMine.exe ModelMine.exe
fi

mkdir -p build
cd build
cmake ..
cmake --build .
