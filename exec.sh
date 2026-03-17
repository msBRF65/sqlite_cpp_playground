#!bin/bash

HOME=/home/dev/sqlite_cpp_playground

# Build the project
cd $HOME
mkdir -p build
cd build
cmake -GNinja ..
ninja

# Run the executable
cd $HOME/build
./app