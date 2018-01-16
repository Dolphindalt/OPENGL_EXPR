#!/bin/bash
# Description: The following script installs dependencies for the project
GREEN='\033[0;32m'
sudo apt-get -qq install libglm-dev make g++ libglew-dev libglew2.0 libsdl2-2.0.0 libsdl2-dev libsdl2-doc -y
mkdir -p lib
cd lib
if [ ! -f lodepng.cpp ]; then
wget https://raw.githubusercontent.com/lvandeve/lodepng/master/lodepng.cpp
fi
if [ ! -f lodepng.h ]; then
wget https://raw.githubusercontent.com/lvandeve/lodepng/master/lodepng.h
fi
echo -e "${GREEN}Successfully installed dependencies"
