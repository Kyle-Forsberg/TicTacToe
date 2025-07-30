#!/bin/bash

set -e

if ! command -v pkg-config &> /dev/null
then
    echo "Error: pkg-config is not installed."
    if [[ "$OSTYPE" == "darwin"* ]]; then
        echo "Install it using: brew install pkg-config"
    else
        echo "Install it using your package manager (e.g. sudo apt install pkg-config)"
    fi
    exit 1
fi

mkdir -p build
cd build
cmake ..
make
cd ..

rm -f game
ln -s build/game game

