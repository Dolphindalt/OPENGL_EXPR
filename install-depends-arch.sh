#!/bin/bash
# Description: arch linux depends for project
sudo pacman -S glm make glew sdl2
mkdir -p lib
cd lib
if [ ! -f lodepng.cpp ]; then
wget https://raw.githubusercontent.com/lvandeve/lodepng/master/lodepng.cpp
fi
if [ ! -f lodepng.h ]; then
wget https://raw.githubusercontent.com/lvandeve/lodepng/master/lodepng.h
fi