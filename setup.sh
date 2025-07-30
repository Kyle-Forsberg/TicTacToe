#!/bin/bash

mkdir build
cd build
cmake ..
make
cd ..
rm -f game	#incase there is already one there for some reason?
ln -s build/game game
